#include <bits/stdc++.h>
#include <ctime>            // For measuring execution time (clock)
#include <unistd.h>         // For sleep on Unix/Linux
#include "Unit_Huffman.hpp" // Your custom Huffman class

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

    while (true)
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

        cout << CYAN << "Enter your choice: " << RESET;
        if (!(cin >> choice))
        {
            cout << RED << "Invalid input. Please enter a number." << RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << endl;

        if (choice == 1)
        {
            cout << "-------------------------------------------------------Compressing File Using "
                 << RED << "Huffman Algorithm"
                 << RESET << " --------------------------------------------------"
                 << endl;

            string Source_file_name, Destination_file_name;
            cout << "Enter the source file name to be compressed: ";
            cin >> Source_file_name;
            cout << "Enter the destination file name to save compressed file: ";
            cin >> Destination_file_name;

            if (Source_file_name == Destination_file_name)
            {
                cout << RED << "Source and destination file names must be different to prevent data loss." << RESET << endl;
                continue;
            }

            ifstream f1(Source_file_name, ios::binary | ios::ate);
            if (!f1.is_open())
            {
                cout << RED << "Error: Could not open source file: " << Source_file_name << RESET << endl;
                continue;
            }

            streampos before = f1.tellg();
            f1.close();

            clock_t tStart = clock();

            try
            {
                Huffman f(Source_file_name, Destination_file_name);
                f.compression();
            }
            catch (const exception &e)
            {
                cout << RED << "Compression failed: " << e.what() << RESET << endl;
                continue;
            }

            cout << endl;
            cout << "Compressed Successfully to file: " << YELLOW << Destination_file_name << RESET << endl;
            sleep(1);
            cout << "Time taken: " << YELLOW << (1.0 * (clock() - tStart) / CLOCKS_PER_SEC) << RESET << " sec" << endl;
            sleep(1);

            ifstream f2(Destination_file_name, ios::binary | ios::ate);
            if (!f2.is_open())
            {
                cout << RED << "Error: Could not open destination file to calculate size." << RESET << endl;
                continue;
            }

            streampos after = f2.tellg();
            f2.close();

            cout << "File Size Before Compressing: " << YELLOW << before << RESET << " Bytes" << endl;
            cout << "File Size After Compressing: " << YELLOW << after << RESET << " Bytes" << endl;

            if (before > 0)
            {
                double compression_Percentage = static_cast<double>(after) * 100.0 / static_cast<double>(before);
                cout << "The size of compressed file is " << YELLOW << fixed << setprecision(2)
                     << compression_Percentage << "%" << RESET << " of the original file." << endl;
            }
            else
            {
                cout << RED << "Warning: Original file size was 0 bytes. Cannot compute compression ratio." << RESET << endl;
            }
        }
        else if (choice == 2)
        {
            cout << "-------------------------------------------------------Decompressing File Using "
                 << RED << "Huffman Algorithm"
                 << RESET << " ------------------------------------------------"
                 << endl;
            string Source_file_name, Destination_file_name;
            cout << "Enter the compressed source file name: ";
            cin >> Source_file_name;
            cout << "Enter the destination file name to save decompressed data: ";
            cin >> Destination_file_name;

            if (Source_file_name == Destination_file_name)
            {
                cout << RED << "Source and destination file names must be different to prevent data loss." << RESET << endl;
                continue;
            }

            ifstream f1(Source_file_name, ios::binary);
            if (!f1.is_open())
            {
                cout << RED << "Error: Could not open compressed source file: " << Source_file_name << RESET << endl;
                continue;
            }
            f1.close();

            clock_t tStart = clock();

            try
            {
                Huffman f(Source_file_name, Destination_file_name);
                f.decompression();
            }
            catch (const exception &e)
            {
                cout << RED << "Decompression failed: " << e.what() << RESET << endl;
                continue;
            }

            ifstream f2(Destination_file_name, ios::binary | ios::ate);
            if (!f2.is_open())
            {
                cout << RED << "Error: Could not open destination file to calculate size." << RESET << endl;
                continue;
            }

            streampos after = f2.tellg();
            f2.close();

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
            break;
        }
        else
        {
            cout << RED << "Invalid choice. Please try again (1, 2 or 3)." << RESET << endl;
        }
    }

    return 0;
}
