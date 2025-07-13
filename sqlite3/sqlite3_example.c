#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	    for (int i = 0; i < argc; i++) {
		            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
			        }
	        printf("-------------\n");
		    return 0;
}

int main() {
	    sqlite3 *db;
	        char *errMsg = 0;

		    /* Open database */
		    if (sqlite3_open("students.db", &db)) {
			            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
				            return 1;
					        } else {
							        printf("Opened database successfully.\n");
								    }

		        /* Create table */
		        const char *create_table_sql =
				        "CREATE TABLE IF NOT EXISTS students("
					        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
						        "name TEXT NOT NULL,"
							        "age INTEGER);";

			    if (sqlite3_exec(db, create_table_sql, 0, 0, &errMsg) != SQLITE_OK) {
				            fprintf(stderr, "SQL error: %s\n", errMsg);
					            sqlite3_free(errMsg);
						        } else {
								        printf("Table created successfully.\n");
									    }

			        /* Insert data */
			        const char *insert_sql =
					        "INSERT INTO students (name, age) VALUES "
						        "('Alice', 20),"
							        "('Bob', 22),"
								        "('Charlie', 19);";

				    if (sqlite3_exec(db, insert_sql, 0, 0, &errMsg) != SQLITE_OK) {
					            fprintf(stderr, "Insert error: %s\n", errMsg);
						            sqlite3_free(errMsg);
							        } else {
									        printf("Inserted records successfully.\n");
										    }

				        /* Read data */
				        printf("\n--- Students Table ---\n");
					    const char *select_sql = "SELECT * FROM students;";
					        sqlite3_exec(db, select_sql, callback, 0, &errMsg);

						    /* Update data */
						    const char *update_sql = "UPDATE students SET age = 21 WHERE name = 'Alice';";
						        if (sqlite3_exec(db, update_sql, 0, 0, &errMsg) != SQLITE_OK) {
								        fprintf(stderr, "Update error: %s\n", errMsg);
									        sqlite3_free(errMsg);
										    } else {
											            printf("Updated Alice's age successfully.\n");
												        }

							    /* Read updated data */
							    printf("\n--- Updated Table ---\n");
							        sqlite3_exec(db, select_sql, callback, 0, &errMsg);

								    /* Delete data */
								    const char *delete_sql = "DELETE FROM students WHERE name = 'Charlie';";
								        if (sqlite3_exec(db, delete_sql, 0, 0, &errMsg) != SQLITE_OK) {
										        fprintf(stderr, "Delete error: %s\n", errMsg);
											        sqlite3_free(errMsg);
												    } else {
													            printf("Deleted Charlie successfully.\n");
														        }

									    /* Read after delete */
									    printf("\n--- After Deletion ---\n");
									        sqlite3_exec(db, select_sql, callback, 0, &errMsg);

										    /* Close database */
										    sqlite3_close(db);
										        return 0;
}

