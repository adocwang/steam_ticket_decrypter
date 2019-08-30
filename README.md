用于解密SteamEncryptedAppTicket的命令行程序，让你可以在轻松在你的php, js, java项目中用steam的加密的应用程序票证来验证用户登录
Steam provides 3 ways to get userId of the player in who's running you game.
1. Get it from client. This is the easiest and the most unsafe way.
2. Get an ticket which client of your game requests from steam. Then you check by an http request to steam.
3. Get an encrypted ticket which client of your game requests from steam. Then you decrypt it with an sdkKey you setted in https://partner.steamgames.com/apps/sdkauth/{yourAppId}

Way 1 is the fastest way but unfase.
Way 2 mabye the most safe way, but realy slow, because you need to wait an http request to finish.
Way 3 maybe safe enough and fast enough for most games. But only C++ libs are provided. If you wan to use this way in servers writen in other languages like php, js, java... It's a lot of work you need to do.
So, I warped things in a command executable which you can call and get output in a lot of languages.

usage:
1. cd to your arch target, then execute sh ./make.sh to build decoder named main
2. run ./main yourAppId yourSteamworksSdkKey SteamEncryptedAppTicket

both yourSteamworksSdkKey and SteamEncryptedAppTicket are using HexString like 1b4b8a2fe2f33ca4532a02653f7f68fd130b3d30ba2828424267848f0b19cb42....

you will get an output like {"code":0,"error":"","steam_id":"76561198539861098"}

yourSteamworksSdkKey can be set in https://partner.steamgames.com/apps/sdkauth/{yourAppId}
