#include <stdio.h>
#include <stdlib.h>
#include <endian.h>

//#include <secp256k1.h>

#include "zcash/Address.hpp"
#include "zcash/Note.hpp"

#include "amount.h"
#include "random.h"
#include "librustzcash.h"

int main( int c , char *argv[]) {

	//unsigned int flags =  SECP256K1_CONTEXT_SIGN;
	//secp256k1_context* ctx = secp256k1_context_create(flags);
	//char* turingsk = "f5109ec8e2b1bec395ca7e24e27aaf22bc0afaeef3e39314591fd488fa6805cd";

	// From here: https://github.com/zcash/zcash/blob/d84f14ec4a9fe96703d85975b2335ea703b7c6f2/src/gtest/test_sapling_note.cpp
    uint64_t v = 0;
    uint64_t note_pos = 0;
    std::array<uint8_t, 11> diversifier{0xf1, 0x9d, 0x9b, 0x79, 0x7e, 0x39, 0xf3, 0x37, 0x44, 0x58, 0x39};
    std::vector<uint8_t> v_sk{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00};
    std::vector<uint8_t> v_pk_d{
        0xdb, 0x4c, 0xd2, 0xb0, 0xaa, 0xc4, 0xf7, 0xeb, 0x8c, 0xa1, 0x31, 0xf1, 0x65, 0x67,
        0xc4, 0x45, 0xa9, 0x55, 0x51, 0x26, 0xd3, 0xc2, 0x9f, 0x14, 0xe3, 0xd7, 0x76, 0xe8,
        0x41, 0xae, 0x74, 0x15};
    std::vector<uint8_t> v_r{
        0x39, 0x17, 0x6d, 0xac, 0x39, 0xac, 0xe4, 0x98, 0x0e, 0xcc, 0x8d, 0x77, 0x8e, 0x89,
        0x86, 0x02, 0x55, 0xec, 0x36, 0x15, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00};
    std::vector<uint8_t> v_cm{
        0xcb, 0x3c, 0xf9, 0x15, 0x32, 0x70, 0xd5, 0x7e, 0xb9, 0x14, 0xc6, 0xc2, 0xbc, 0xc0,
        0x18, 0x50, 0xc9, 0xfe, 0xd4, 0x4f, 0xce, 0x08, 0x06, 0x27, 0x8f, 0x08, 0x3e, 0xf2,
        0xdd, 0x07, 0x64, 0x39};
    std::vector<uint8_t> v_nf{
        0x44, 0xfa, 0xd6, 0x56, 0x4f, 0xfd, 0xec, 0x9f, 0xa1, 0x9c, 0x43, 0xa2, 0x8f, 0x86,
        0x1d, 0x5e, 0xbf, 0x60, 0x23, 0x46, 0x00, 0x7d, 0xe7, 0x62, 0x67, 0xd9, 0x75, 0x27,
        0x47, 0xab, 0x40, 0x63};
    uint256 sk(v_sk);
    uint256 pk_d(v_pk_d);
    uint256 r(v_r);
    uint256 cm(v_cm);
    uint256 nf(v_nf);

    // Test commitment
    SaplingNote note = SaplingNote(diversifier, pk_d, v, r);
    ASSERT_EQ(note.cm().get(), cm);

    // Test nullifier
    SaplingSpendingKey spendingKey(sk);
    ASSERT_EQ(note.nullifier(spendingKey.full_viewing_key(), note_pos), nf);

	printf("Test passed");
	return 0;
}