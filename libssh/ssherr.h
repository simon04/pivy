/*	$OpenBSD: ssherr.h,v 1.3 2015/01/30 01:13:33 djm Exp $	*/
/*
 * Copyright (c) 2011 Damien Miller
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _SSHERR_H
#define _SSHERR_H

/* XXX are these too granular? not granular enough? I can't decide - djm */

/* Error codes */
#define SSH_ERR_SUCCESS				0
#define SSH_ERR_INTERNAL_ERROR			-1
#define SSH_ERR_ALLOC_FAIL			-2
#define SSH_ERR_MESSAGE_INCOMPLETE		-3
#define SSH_ERR_INVALID_FORMAT			-4
#define SSH_ERR_BIGNUM_IS_NEGATIVE		-5
#define SSH_ERR_STRING_TOO_LARGE		-6
#define SSH_ERR_BIGNUM_TOO_LARGE		-7
#define SSH_ERR_ECPOINT_TOO_LARGE		-8
#define SSH_ERR_NO_BUFFER_SPACE			-9
#define SSH_ERR_INVALID_ARGUMENT		-10
#define SSH_ERR_KEY_BITS_MISMATCH		-11
#define SSH_ERR_EC_CURVE_INVALID		-12
#define SSH_ERR_KEY_TYPE_MISMATCH		-13
#define SSH_ERR_KEY_TYPE_UNKNOWN		-14 /* XXX UNSUPPORTED? */
#define SSH_ERR_EC_CURVE_MISMATCH		-15
#define SSH_ERR_EXPECTED_CERT			-16
#define SSH_ERR_KEY_LACKS_CERTBLOB		-17
#define SSH_ERR_KEY_CERT_UNKNOWN_TYPE		-18
#define SSH_ERR_KEY_CERT_INVALID_SIGN_KEY	-19
#define SSH_ERR_KEY_INVALID_EC_VALUE		-20
#define SSH_ERR_SIGNATURE_INVALID		-21
#define SSH_ERR_LIBCRYPTO_ERROR			-22
#define SSH_ERR_UNEXPECTED_TRAILING_DATA	-23
#define SSH_ERR_SYSTEM_ERROR			-24
#define SSH_ERR_KEY_CERT_INVALID		-25
#define SSH_ERR_AGENT_COMMUNICATION		-26
#define SSH_ERR_AGENT_FAILURE			-27
#define SSH_ERR_DH_GEX_OUT_OF_RANGE		-28
#define SSH_ERR_DISCONNECTED			-29
#define SSH_ERR_MAC_INVALID			-30
#define SSH_ERR_NO_CIPHER_ALG_MATCH		-31
#define SSH_ERR_NO_MAC_ALG_MATCH		-32
#define SSH_ERR_NO_COMPRESS_ALG_MATCH		-33
#define SSH_ERR_NO_KEX_ALG_MATCH		-34
#define SSH_ERR_NO_HOSTKEY_ALG_MATCH		-35
#define SSH_ERR_NO_HOSTKEY_LOADED		-36
#define SSH_ERR_PROTOCOL_MISMATCH		-37
#define SSH_ERR_NO_PROTOCOL_VERSION		-38
#define SSH_ERR_NEED_REKEY			-39
#define SSH_ERR_PASSPHRASE_TOO_SHORT		-40
#define SSH_ERR_FILE_CHANGED			-41
#define SSH_ERR_KEY_UNKNOWN_CIPHER		-42
#define SSH_ERR_KEY_WRONG_PASSPHRASE		-43
#define SSH_ERR_KEY_BAD_PERMISSIONS		-44
#define SSH_ERR_KEY_CERT_MISMATCH		-45
#define SSH_ERR_KEY_NOT_FOUND			-46
#define SSH_ERR_AGENT_NOT_PRESENT		-47
#define SSH_ERR_AGENT_NO_IDENTITIES		-48
#define SSH_ERR_BUFFER_READ_ONLY		-49
#define SSH_ERR_KRL_BAD_MAGIC			-50
#define SSH_ERR_KEY_REVOKED			-51
#define SSH_ERR_CONN_CLOSED			-52
#define SSH_ERR_CONN_TIMEOUT			-53
#define SSH_ERR_CONN_CORRUPT			-54
#define SSH_ERR_PROTOCOL_ERROR			-55

/* Translate a numeric error code to a human-readable error string */
const char *ssh_err(int n);

#define ssherrf(func, code, ...)		\
    errf(((code) == SSH_ERR_MESSAGE_INCOMPLETE) ? "IncompleteMessageError" : \
    "LibSSHError", NULL, func " returned %d (%s)", ##__VA_ARGS__, \
    code, ssh_err(code))

#define make_sslerrf(var, call, action, ...)	\
	do {	\
		char _ssl_errbuf[128]; \
		unsigned long _ssl_err = ERR_peek_last_error(); \
		ERR_load_crypto_strings(); \
		ERR_error_string(_ssl_err, _ssl_errbuf); \
		var = errf("OpenSSLError", NULL, \
		    call " returned error %u (%s) while " action, \
		    _ssl_err, _ssl_errbuf, ##__VA_ARGS__); \
	} while (0)

#endif /* _SSHERR_H */
