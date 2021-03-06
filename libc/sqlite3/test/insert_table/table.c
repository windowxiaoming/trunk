#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"


#define PATH_DATABASE ("./test.db")


#define SQLITE3_LOG(fmt, arg...)  \
		printf("[%s:%d] "fmt"\n", __func__, __LINE__, ##arg)

/*
 * pv: The 4th argument to sqlite3_exec() is relayed through to the 1st argument of sqlite_callback() 
 * argc: The 2nd argument to the sqlite_callback() is the number of columns in the result 
 * argv: The 3rd argument to the sqlite3_callback() is an array of pointers to strings obtained as if from sqlite3_column_text()
 *
 * */
static int sqlite_callback(void *pv, int argc, char **argv, char **azColName)
{
	SQLITE3_LOG("enter");
	int i;
	for(i=0; i<argc; i++)
	{
		SQLITE3_LOG("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

/* callback */
int main(int argc, char** argv)
{
	sqlite3* pDb = NULL;
	int nRet = SQLITE_ERROR;
	char* pcSQL = NULL;
	char* pcErrmsg = NULL;

	/* open  database */
	nRet = sqlite3_open(PATH_DATABASE, &pDb);
	if (nRet != SQLITE_OK)
	{
		SQLITE3_LOG("open database error:%s\n", sqlite3_errmsg(pDb));
		return -1;
	}
	SQLITE3_LOG("open database success\n");

	/* create SQL statement */
	pcSQL ="INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		   "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
		   "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		   "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
		   "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		   "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
		   "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		   "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

	/* execute SQL statement */
	nRet = sqlite3_exec(pDb, pcSQL, sqlite_callback, NULL, &pcErrmsg);
	if (nRet != SQLITE_OK)
	{
		SQLITE3_LOG("exec sql  error(%d):%s\n", nRet, pcErrmsg);
		sqlite3_free(pcErrmsg);
		return -1;
	}
	SQLITE3_LOG("insert table success\n");

	sqlite3_close(pDb);
	return 0;
}
