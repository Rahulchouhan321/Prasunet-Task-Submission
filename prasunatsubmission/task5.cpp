#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <gumbo.h>

// Function to write data received from libcurl to a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

// Function to fetch HTML content from a URL
std::string fetchHTML(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string html;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return html;
}

// Function to search for product names in the HTML document using Gumbo
void searchForProductNames(GumboNode* node, std::vector<std::string>& productNames) {
    if (node->type != GUMBO_NODE_ELEMENT) return;
    
    GumboAttribute* classAttr;
    if (node->v.element.tag == GUMBO_TAG_DIV && 
        (classAttr = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
        std::string(classAttr->value).find("product-name") != std::string::npos) {

        if (node->v.element.children.length > 0) {
            GumboNode* textNode = static_cast<GumboNode*>(node->v.element.children.data[0]);
            if (textNode->type == GUMBO_NODE_TEXT) {
                productNames.push_back(textNode->v.text.text);
            }
        }
    }
    
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        searchForProductNames(static_cast<GumboNode*>(children->data[i]), productNames);
    }
}

// Function to extract product names from HTML
std::vector<std::string> extractProductNames(const std::string& html) {
    std::vector<std::string> productNames;
    GumboOutput* output = gumbo_parse(html.c_str());
    searchForProductNames(output->root, productNames);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
    return productNames;
}

// Function to save product names to a CSV file
void saveToCSV(const std::vector<std::string>& productNames, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Product Name\n";
        for (const auto& name : productNames) {
            file << name << "\n";
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main() {
    const std::string url = "https://example.com/products";
    const std::string html = fetchHTML(url);
    const std::vector<std::string> productNames = extractProductNames(html);

    saveToCSV(productNames, "products.csv");

    std::cout << "Product names have been saved to products.csv" << std::endl;
    return 0;
}
