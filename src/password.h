/**
* Holds all of the password data.
*/
typedef struct password {
	char pass[9];
	char salt[8];
	char *hash;

} password;

/**
 * Global password vault to store password.
 */
password *vault;
