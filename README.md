cd to your arch target, then execute sh ./make.sh to build decoder named main

usage:

./main yourAppId yourSteamworksSdkKey encryptedTicketYouWantToDecrypt

both yourSteamworksSdkKey and encryptedTicketYouWantToDecrypt are HexString like 1b4b8a2fe2f33ca4532a02653f7f68fd130b3d30ba2828424267848f0b19cb42....

you will get an output like {"code":0,"error":"","steam_id":"76561198539861098"}

yourSteamworksSdkKey can be set in https://partner.steamgames.com/apps/sdkauth/{yourAppId}