#include "custom_sounds.hpp"

__forceinline void setup_sounds()
{
	CreateDirectory("csgo\\sound", nullptr);
	FILE* file = nullptr;

	file = fopen(crypt_str("csgo\\sound\\skeet.wav"), crypt_str("wb"));
	fwrite(skeet, sizeof(unsigned char), 64700, file); //-V575
	fclose(file);

	file = fopen(crypt_str("csgo\\sound\\cod.wav"), crypt_str("wb"));
	fwrite(cod, sizeof(unsigned char), 11752, file);
	fclose(file);

	file = fopen(crypt_str("csgo\\sound\\bameware.wav"), crypt_str("wb"));
	fwrite(bameware, sizeof(unsigned char), 105522, file);
	fclose(file);

	file = fopen(crypt_str("csgo\\sound\\flick.wav"), crypt_str("wb"));
	fwrite(flick, sizeof(unsigned char), 152168, file);
	fclose(file);

	file = fopen(crypt_str("csgo\\sound\\snazzy.wav"), crypt_str("wb"));
	fwrite(snazzy, sizeof(unsigned char), 66918, file);
	fclose(file);

	file = fopen(crypt_str("csgo\\sound\\snazzy2.wav"), crypt_str("wb"));
	fwrite(snazzy2, sizeof(unsigned char), 66918, file);
	fclose(file);

	file = fopen(crypt_str("csgo\\sound\\bucket.wav"), crypt_str("wb"));
	fwrite(bucket, sizeof(unsigned char), 30684, file);
	fclose(file);
}