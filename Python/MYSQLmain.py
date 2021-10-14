from sys import argv
from authDB import get_auth_data
import dbInteraction
from mysql.connector import connect, Error

user, password = get_auth_data()

try:
    with connect(
            host="localhost",
            user=user,
            password=password,
            database="users",
    ) as connection:
        if argv[1] == "AUTH":
            print(dbInteraction.auth(connection.cursor(), argv[2], argv[3]))
except Error as e:
    print(e)
