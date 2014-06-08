#include <string>
#include <vector>

#include "key.h"
#include "base58.h"
#include "uint256.h"
#include "util.h"

using namespace std;


int main()
{
    vector<unsigned char> secret = new vector();
    secret.push_back(250);
    secret.push_back(99);
    secret.push_back(82);
    secret.push_back(30);
    secret.push_back(51);
    secret.push_back(62);
    secret.push_back(75);
    secret.push_back(159);
    secret.push_back(106);
    secret.push_back(152);
    secret.push_back(161);
    secret.push_back(66);
    secret.push_back(104);
    secret.push_back(13);
    secret.push_back(58);
    secret.push_back(239);
    secret.push_back(77);
    secret.push_back(142);
    secret.push_back(127);
    secret.push_back(121);
    secret.push_back(114);
    secret.push_back(60);
    secret.push_back(224);
    secret.push_back(4);
    secret.push_back(54);
    secret.push_back(145);
    secret.push_back(219);
    secret.push_back(85);
    secret.push_back(195);
    secret.push_back(107);
    secret.push_back(217);
    secret.push_back(5);
    CKey key;
    key.SetSecret(secret, fCompressed);
    key.GetPubKey();
    printf("    * pubkey (hex): %s\n", HexStr(key.GetPubKey()).c_str());
}
