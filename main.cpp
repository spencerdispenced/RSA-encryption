// main.cpp

#include "GMPStringUtilities.h"

using namespace std;

int main(int argc, char const *argv[])
{

    if (argc < 2)
    {
        cerr << "No input file detected" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    string filename = argv[1];

    string str = "";
    string line = "";

    int pos = filename.find_last_of(".");
    string extension = filename.substr(pos);

    if (extension != ".txt" && extension != ".rsa")
    {
        cerr << "Invalid input type, must input a '.txt' or '.rsa' file." << endl;
        return 1;
    }


    while(getline(fin,line))
    {
        str += line + '\n'; 
    }


    /*setup key generation */
    mpz_class n;
    mpz_class e = 65537;
    mpz_class p;
    p = "33478071698956898786044169848212690817704794983713768568912431388982883793878002287614711652531743087737814467999489";


    mpz_class q;
    q = "36746043666799590428244633799627952632279158164343087642676032283815739666511279233373417143396810270092798736308917";

    mpz_mul(n.get_mpz_t(),p.get_mpz_t(),q.get_mpz_t());// compute n

    mpz_class p2;
    p2 = p - 1;
  
    mpz_class q2;
    q2 = q - 1; 

    mpz_class t;
    mpz_mul(t.get_mpz_t(),p2.get_mpz_t(),q2.get_mpz_t()); // compute totient

    mpz_class d; 
    mpz_invert(d.get_mpz_t(), e.get_mpz_t(),t.get_mpz_t()); // compute d 


    if (extension == ".txt")
    {
        mpz_class m = from_string(str); 

        string outputFileName = filename.substr(0,filename.find_last_of('.')) + ".rsa";

        cout << filename << " encrypted\n" << outputFileName << " has been created." << endl;

        /*encrypt message*/
        mpz_class cipher;
        mpz_powm_sec(cipher.get_mpz_t(), m.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
        
        ofstream outputfile(outputFileName);
        outputfile << cipher;
    }

    if (extension == ".rsa")
    {
        mpz_class m;
        m = str;

        string outputFileName = filename.substr(0,filename.find_last_of('.')) + ".decrypted";

        cout << filename << " decrypted\n" << outputFileName << " has been created." << endl;

        /*decrypt message*/
        mpz_class plain;
        mpz_powm_sec(plain.get_mpz_t(), m.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());

        ofstream outputfile(outputFileName);
        outputfile << to_string(plain);
    }
}
