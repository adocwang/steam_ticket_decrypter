#include "stdlib.h"
#include "time.h"
#include <string>
#include "steam/steamencryptedappticket.h"

using namespace std;
/**
 *encrypted ticket length:126, data:080110bb9dc8880c180020462a70f000fe20e500c96a18bd477245c1ca6b8909227d36371773cad7035549ffc4452205116f4bec8ae51ec5c9a9189f2b63b8419b2fcca2308c43343899d27753a69b98bc2c2a2e85a2a851a484a9e9a687ae940f78447381943aa61317f3e1b71007264ca3ece3bae028ef6bc411ff19ab 
 * 
 **/

void error(int code, string error){
    printf("{\"code\":%d,\"error\":\"%s\",\"steam_id\":\"\"}", code, error.c_str());
}

void success(uint64 steamId){
    printf("{\"code\":0,\"error\":\"\",\"steam_id\":\"%llu\"}", steamId);
}

uint8 hexStrToUint8(char* string, uint8_t * data) {
    if (string == NULL) return 0;
    uint8 slength = strlen(string);
    if ((slength % 2) != 0) // must be even
        return 0;

    uint8 dlength = slength / 2;

    uint8 index = 0;
    while (index < slength) {
        char c = string[index];
        int value = 0;
        if (c >= '0' && c <= '9')
            value = (c - '0');
        else if (c >= 'A' && c <= 'F')
            value = (10 + (c - 'A'));
        else if (c >= 'a' && c <= 'f')
            value = (10 + (c - 'a'));
        else
            return 0;

        data[(index / 2)] += value << (((index + 1) % 2) * 4);

        index++;
    }

    return dlength;
}

int main(int argc, char *argv[])
{
    // printf("running %s\n", argv[0]);
    uint8 rgubTicket[1024];
    uint32 appId = atoi(argv[1]);
    // printf("appid %u!\n", appId);
    uint8 rgubKey[k_nSteamEncryptedAppTicketSymmetricKeyLen];
    hexStrToUint8(argv[2], rgubKey);
    uint8 cubTicket = hexStrToUint8(argv[3], rgubTicket);
    // printf("length %u\n", cubTicket);

    uint8 rgubDecrypted[1024];
    uint32 cubDecrypted = sizeof(rgubDecrypted);
    if (!SteamEncryptedAppTicket_BDecryptTicket(rgubTicket, cubTicket, rgubDecrypted, &cubDecrypted, rgubKey, sizeof(rgubKey)))
    {
        error(-1, "Ticket failed to decrypt");
        return 0;
    }
    // printf("Ticket decrypt success!\n");

    if (!SteamEncryptedAppTicket_BIsTicketForApp(rgubDecrypted, cubDecrypted, appId))
    {
        error(-2, "Ticket for wrong app id");
        return 0;
    }
    // printf("AppId check success!\n");

    CSteamID steamIDFromTicket;
    SteamEncryptedAppTicket_GetTicketSteamID(rgubDecrypted, cubDecrypted, &steamIDFromTicket);
    // printf("userId %llu!\n", steamIDFromTicket.ConvertToUint64());
    success(steamIDFromTicket.ConvertToUint64());
    // if (steamIDFromTicket != SteamUser()->GetSteamID())
    // {
    //     printf("Ticket for wrong user\n");
    // }
    // uint32 cubData;
    // uint32 *punSecretData = (uint32 *)SteamEncryptedAppTicket_GetUserVariableData(rgubDecrypted, cubDecrypted, &cubData);
    // if (cubData != sizeof(uint32) || *punSecretData != k_unSecretData)
    // {
    //     printf("Failed to retrieve secret data\n");
    // }
}
