// GMPStringUtilities.h
//
// Provides simple methods for converting string to numerical numbers as GMP
// objects and back.
//

#pragma once

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>
#include <gmpxx.h>
#include <vector>
#include <fstream>



mpz_class from_string(std::string message)
{
   mpz_class gmp_message(0);

   size_t size(message.size());

   std::stringstream ss;
   ss << std::setfill('0');
   for (size_t i = 0; i < size; ++i)
   {
      auto ascii = static_cast<int>(message[i]);
      ss << std::setw(3) << ascii;
      ss.clear();
      ss.str("");

      mpz_class temp(10);
      mpz_pow_ui(temp.get_mpz_t(), temp.get_mpz_t(), (3 * (size - i) - 3));
      gmp_message = gmp_message + temp * ascii;
   }

   return gmp_message;
}

std::string to_string(mpz_class gmp_message)
{
   std::string message = gmp_message.get_str();
   size_t size(message.size());

   while (size % 3 != 0)
   {
      message = "0" + message;
      size = message.size();
   }

   std::string original;
   original.resize(size/3);

   for (size_t i = size; i > 0; i-=3)
   {
      std::string sub = message.substr(i-3, 3);
      original[(i/3)-1] = static_cast<char>(std::stoi(sub));
   }

   return original;
}

