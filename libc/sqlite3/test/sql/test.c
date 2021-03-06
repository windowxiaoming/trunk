#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sql.h"

#define SQLITE3_LOG(fmt, arg...)  \
		printf("[%s:%d] "fmt"\n", __func__, __LINE__, ##arg)

#define PATH_DATABASE ("./test.db")

int main(int argc, char** argv)
{
	char* pcSQL = NULL;
	char* pcErrmsg = NULL;
	int nRet = SQLITE_ERROR;
	SQL_HANDLE_S* pSqlHandle = (SQL_HANDLE_S*)initSqlHandle();
	int nUserID = -1;

	pcSQL = pSqlHandle->m_sSqlCmd.m_pcSql;
	//pcSQL = (char*)malloc(SQL_LEN);
	//memset(pcSQL,'\0', 256);

	if (0 == access(PATH_DATABASE, F_OK))
	{
		if (SQLITE_OK != sql_open_db_rw(pSqlHandle, PATH_DATABASE))	
		{
			SQLITE3_LOG("open database failed");
			destroySqlHandle(pSqlHandle);
			return -1;
		}
		SQLITE3_LOG("open database success!");	
	}
	else
	{
		if (SQLITE_OK != sql_create_db(pSqlHandle, PATH_DATABASE))
		{
			SQLITE3_LOG("create database failed");
			destroySqlHandle(pSqlHandle);
			return -1;
		}
		SQLITE3_LOG("create database success!");	

#if 1
		//创建表
		sprintf(pcSQL, "CREATE TABLE ALBUM(USERID INT NOT NULL,DATAID INT NOT NULL,NAME TEXT NOT NULL,AGE INT,GENDER TEXT);");
		sql_create_table(pSqlHandle, pcSQL);
#endif
		
#if 1
		//插入记录
		sprintf(pcSQL, "INSERT INTO ALBUM (USERID,DATAID,NAME) VALUES (0, 0, 'frank');");
		sql_insert_record(pSqlHandle, pcSQL);
		sprintf(pcSQL, "INSERT INTO ALBUM (USERID,DATAID,NAME) VALUES (0, 1, 'frank');");
		sql_insert_record(pSqlHandle, pcSQL);
		sprintf(pcSQL, "INSERT INTO ALBUM (USERID,DATAID,NAME) VALUES (0, 2, 'frank');");
		sql_insert_record(pSqlHandle, pcSQL);
		sprintf(pcSQL, "INSERT INTO ALBUM (USERID,DATAID,NAME) VALUES (0, 3, 'frank');");
		sql_insert_record(pSqlHandle, pcSQL);
#endif
	}

#if 0
	//插入记录
	sprintf(pcSQL, "INSERT INTO ALBUM (USERID,DATAID,NAME) VALUES (1, 0, 'zhangsan');INSERT INTO ALBUM (USERID,DATAID,NAME) VALUES (2, 0, 'lisi');INSERT INTO ALBUM (USERID,DATAID,NAME) VALUES (3, 0, 'wangwu');INSERT INTO ALBUM (USERID,DATAID,NAME) VALUES (4, 0, 'zhaoliu');");
	sql_insert_record(pSqlHandle, pcSQL);
#endif

#if 0
		//插入记录
		sprintf(pcSQL, "INSERT INTO ALBUM (USERID,DATAID,NAME) VALUES (1, 0, 'zhangsan');");
		sql_insert_record(pSqlHandle, pcSQL);
		sprintf(pcSQL, "INSERT INTO ALBUM (USERID,DATAID,NAME) VALUES (1, 1, 'zhangsan');");
		sql_insert_record(pSqlHandle, pcSQL);
		sprintf(pcSQL, "INSERT INTO ALBUM (USERID,DATAID,NAME) VALUES (1, 2, 'zhangsan');");
		sql_insert_record(pSqlHandle, pcSQL);
		sprintf(pcSQL, "INSERT INTO ALBUM (USERID,DATAID,NAME) VALUES (1, 3, 'zhangsan');");
		sql_insert_record(pSqlHandle, pcSQL);
#endif

#if 0
	//查询指定记录
	sprintf(pcSQL, "SELECT * FROM ALBUM WHERE USERID=%d AND DATAID=%d;", 0, 0);
	sql_query_record(pSqlHandle, pcSQL);

	if ((-1 != pSqlHandle->m_sPerson.m_nAlbumUserId) && (-1 != pSqlHandle->m_sPerson.m_nAlbumUserDataId))
		SQLITE3_LOG("userid=%d, dataid=%d, name=%s",pSqlHandle->m_sPerson.m_nAlbumUserId, pSqlHandle->m_sPerson.m_nAlbumUserDataId, pSqlHandle->m_sPerson.m_acName);
	else
		SQLITE3_LOG("userid=%d, dataid=%d, is not exist", 0, 0);
#endif

#if 0
	//删除指定记录
	//sprintf(pcSQL, "DELETE FROM ALBUM WHERE USERID=%d AND DATAID=%d;", 1, 0);
	//sql_rm_record(pSqlHandle, pcSQL);
	sprintf(pcSQL, "DELETE FROM ALBUM WHERE USERID=%d AND DATAID=%d;", 2, 0);
	sql_rm_record(pSqlHandle, pcSQL);
	sprintf(pcSQL, "DELETE FROM ALBUM WHERE USERID=%d AND DATAID=%d;", 3, 0);
	sql_rm_record(pSqlHandle, pcSQL);
	sprintf(pcSQL, "DELETE FROM ALBUM WHERE USERID=%d AND DATAID=%d;", 4, 0);
	sql_rm_record(pSqlHandle, pcSQL);
#endif

#if 0
	//修改记录
	sprintf(pcSQL, "UPDATE ALBUM SET NAME='FJ' WHERE USERID=0 AND DATAID=0");
	sql_update_record(pSqlHandle, pcSQL);
#endif

#if 1
	nUserID = 0;
	sprintf(pcSQL, "SELECT * FROM ALBUM WHERE USERID=%d AND NAME='%s';", nUserID, "frank");
	sql_query_record(pSqlHandle, pcSQL);

	if (-1 != pSqlHandle->m_sPerson.m_nAlbumUserId)
	{
		int i = 0;

		SQLITE3_LOG("userid=%d, name=%s",pSqlHandle->m_sPerson.m_nAlbumUserId, pSqlHandle->m_sPerson.m_acName);
		for (i = 0; i < DATAID_MAX; ++i)
			SQLITE3_LOG("dataid[%d]=%d",i,pSqlHandle->m_sPerson.m_nAlbumUserDataId[i]);
	}
	else
		SQLITE3_LOG("userid=%d, is not exist", nUserID);
#endif

#if 0
	//查询记录
	sprintf(pcSQL, "SELECT * FROM ALBUM ORDER BY USERID;");
	sql_query_record_all(pSqlHandle, pcSQL);
#endif

	if (SQLITE_OK != sql_close_db(pSqlHandle))
	{
		SQLITE3_LOG("close database failed");
		destroySqlHandle(pSqlHandle);
		return -1;
	}

	//if (NULL != pcSQL)
	//	free(pcSQL);

	destroySqlHandle(pSqlHandle);

	return 0;
}
