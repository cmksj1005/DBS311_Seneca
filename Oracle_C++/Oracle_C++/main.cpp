#include <iostream>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

struct ShoppingCart {
	int product_id;
	double price;
	int quantity;
};

int main(void) {
	/* OCCI Variables */
	Environment* env = nullptr;
	Connection* conn = nullptr;
	Statement* stmt = nullptr;
	ResultSet* rs = nullptr;
	/* Used Variables */
	string str;
	string user = "dbs311_232ncc15";
	string pass = "19030228";
	string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";
	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(user, pass, constr);

		stmt = conn->createStatement("SELECT * FROM student WHERE s_id = :1");
		stmt->setInt(1, 1004);
		rs = stmt->executeQuery();

		if (!rs->next()) {
			// if the result set is empty
			cout << "ResultSet is empty." << endl;
		}
		else {
			// if the result set in not empty
			do {
				if (!rs->isNull(2)) { //if the column name is not null
					cout << "Student ID: " << rs->getInt(1) << " Student Name: " << rs->getString(2) << endl;
				}
				else {
					cout << "Student ID: " << rs->getInt(1) << " Student Name: " << "Unknown" << endl;
				}
			} while (rs->next()); //if there is more rows, iterate
		}

		conn->terminateStatement(stmt);
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	return 0;
}