#include <bits/stdc++.h>
#include <ctime>
#include <unistd.h>
#include "Unit_Huffman.hpp"

using namespace std;

int main()
{
    const string RED = "\033[31m";
    const string PINK = "\033[35m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN = "\033[36m";
    const string BOLD = "\033[1m";
    const string RESET = "\033[0m";

    do
    {
        int choice;
        cout << endl;
        cout << "-------------------------------------------------------WELCOME TO "
             << RED << "File" << RESET
             << PINK << "Re" << RESET
             << BLUE << "Sizer" << RESET
             << "--------------------------------------------------------------"
             << endl;

        cout << endl;
        cout << RED << "--> Enter " << BOLD << 1 << RESET << RED << " for Compressing a file." << RESET << endl;
        cout << PINK << "--> Enter " << BOLD << 2 << RESET << PINK << " for Decompressing a file." << RESET << endl;
        cout << BLUE << "--> Enter " << BOLD << 3 << RESET << BLUE << " for Exiting." << RESET << endl;

        cin >> choice;
        cout << endl;

        if (choice == 1)
        {
            cout << "-------------------------------------------------------Compressing File Using "
                 << RED << "Huffman Algorithm"
                 << RESET << " --------------------------------------------------"
                 << endl;

            string Source_file_name;
            cout << "Enter the source file name to be compressed: ";
            cin >> Source_file_name;
            string Destination_file_name;
            cout << "Enter the destination file name to save compressed file: ";
            cin >> Destination_file_name;

            if (Source_file_name == Destination_file_name)
            {
                cout << RED << "Source and destination file names must be different to prevent data loss." << RESET << endl;
                continue;
            }

            clock_t tStart = clock();
            ifstream f1(Source_file_name, ios::binary | ios::ate);
            int before = f1.tellg();

            Huffman f(Source_file_name, Destination_file_name);
            f.compression();

            cout << endl;
            cout << "Compressed Successfully to file: " << YELLOW << Destination_file_name << RESET << endl;
            sleep(1);
            cout << "Time taken: " << YELLOW << (1.0 * (clock() - tStart) / CLOCKS_PER_SEC) << RESET << " sec" << endl;
            sleep(1);

            ifstream f2(Destination_file_name, ios::binary | ios::ate);
            int after = f2.tellg();

            cout << "File Size Before Compressing: " << YELLOW << before << RESET << " Bytes" << endl;
            cout << "File Size After Compressing: " << YELLOW << after << RESET << " Bytes" << endl;

            double compression_Percentage = (double)after * 100 / before;
            cout << "The size of compressed file is " << YELLOW << fixed << setprecision(2)
                 << compression_Percentage << "%" << RESET << " of the original file." << endl;
        }
        else if (choice == 2)
        {
            cout << "-------------------------------------------------------Decompressing File Using "
                 << RED << "Huffman Algorithm"
                 << RESET << " ------------------------------------------------"
                 << endl;

            string Source_file_name;
            cout << "Enter the compressed source file name: ";
            cin >> Source_file_name;
            string Destination_file_name;
            cout << "Enter the destination file name to save decompressed data: ";
            cin >> Destination_file_name;

            if (Source_file_name == Destination_file_name)
            {
                cout << RED << "Source and destination file names must be different to prevent data loss." << RESET << endl;
                continue;
            }

            clock_t tStart = clock();

            Huffman f(Source_file_name, Destination_file_name);
            f.decompression();

            ifstream f1(Destination_file_name, ios::binary | ios::ate);
            int after = f1.tellg();

            cout << endl;
            cout << "File Size After Decompressing: " << YELLOW << after << RESET << " Bytes" << endl;
            sleep(1);
            cout << "Decompressed Successfully to file: " << YELLOW << Destination_file_name << RESET << endl;
            sleep(1);
            cout << "Time taken: " << YELLOW << (1.0 * (clock() - tStart) / CLOCKS_PER_SEC) << RESET << " sec" << endl;
        }
        else if (choice == 3)
        {
            cout << CYAN << "Thank You! Have A Nice Day." << RESET << endl;
            exit(0);
        }
        else
        {
            cout << RED << "Invalid choice. Please try again." << RESET << endl;
        }

    } while (1);

    return 0;
}
