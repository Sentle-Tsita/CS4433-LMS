#include <gtest/gtest.h>
#include <sodium.h>

#include <array>
#include <string>

using namespace std;

namespace {

using Hash = array<unsigned char, 32>;
using Salt = array<unsigned char, crypto_pwhash_SALTBYTES>;

Hash hashPassword(const string& password, const Salt& salt) {
    Hash hash{};
    int result = crypto_pwhash(hash.data(), hash.size(), password.c_str(), password.size(), salt.data(),
                               crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE,
                               crypto_pwhash_ALG_DEFAULT);
    EXPECT_EQ(result, 0);
    return hash;
}

}  // namespace

TEST(LibsodiumTrial, SamePasswordAndSaltGiveSameHash) {
    ASSERT_GE(sodium_init(), 0);
    Salt salt{};
    randombytes_buf(salt.data(), salt.size());

    Hash stored = hashPassword("correct horse", salt);
    Hash again = hashPassword("correct horse", salt);

    EXPECT_EQ(sodium_memcmp(stored.data(), again.data(), stored.size()), 0);
}

TEST(LibsodiumTrial, WrongPasswordGivesDifferentHash) {
    ASSERT_GE(sodium_init(), 0);
    Salt salt{};
    randombytes_buf(salt.data(), salt.size());

    Hash stored = hashPassword("correct horse", salt);
    Hash wrong = hashPassword("wrong horse", salt);

    EXPECT_NE(sodium_memcmp(stored.data(), wrong.data(), stored.size()), 0);
}

TEST(LibsodiumTrial, DifferentSaltGivesDifferentHash) {
    ASSERT_GE(sodium_init(), 0);
    Salt first{}, second{};
    randombytes_buf(first.data(), first.size());
    randombytes_buf(second.data(), second.size());

    Hash a = hashPassword("same password", first);
    Hash b = hashPassword("same password", second);

    EXPECT_NE(sodium_memcmp(a.data(), b.data(), a.size()), 0);
}