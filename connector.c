#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
 FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char delimiter[] = ":";
    char *array[8];
    int i;
  MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;

   char *server = "192.168.0.32";
   char *user = "root";
   char *password = "admin"; /* set me first */
   char *database = "db_memory";

 char query[2000];

   conn = mysql_init(NULL);

   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }


    fp = fopen("send.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
     i = 0;

      //  printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
    char *p = strtok (line, ":");
	  while (p != NULL)
     {
        array[i++] = p;
        p = strtok (NULL, ":");

     }
sprintf(query," INSERT INTO `db_memory`.`pagefault`(`idXEN`,`idVM`,`time`,`process_id`,`faultadresss`,`faultacccess`,`page_type`,`fault_entry_time`) VALUES (%s, %s,%s, %s, '%s', '%s', '%s', %s);",1, array[0],array[1],array[2],array[3],array[4],array[5],array[6], "\n"));
printf("%s", query);
if (mysql_query(conn,query)   !=0)                
	{                                                                                                  
	fprintf(stderr, "Query Failure\n");                                                              
	return EXIT_FAILURE;                                                                             
  }  
    }
	
    fclose(fp);
    if (line)
        free(line);


 for (i = 0; i < 8; ++i) 
        printf("%s\n", array[i]);

 

   /* send SQL query */
   if (mysql_query(conn, "show tables")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

   res = mysql_use_result(conn);

   /* output table name */
   printf("MySQL Tables in mysql database:\n");
   while ((row = mysql_fetch_row(res)) != NULL)
      printf("%s \n", row[0]);

	if (mysql_query(conn, " INSERT INTO `db_memory`.`pagefault`(`idXEN`,`idVM`,`time`,`process_id`,`faultadresss`,`faultacccess`,`page_type`,`fault_entry_time`) VALUES (1,1,1,1,1,1,1,1);") !=0)                   
	{                                                                                                  
	fprintf(stderr, "Query Failure\n");                                                              
	return EXIT_FAILURE;                                                                             
  }                       

   /* close connection */
   mysql_free_result(res);
   mysql_close(conn);
	return 0;
}
