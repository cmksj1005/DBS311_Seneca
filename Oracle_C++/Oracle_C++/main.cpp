#include <iostream>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

int main(void) {
	/* OCCI Variables */
	Environment* env = nullptr;
	Connection* conn = nullptr;
	Statement* stmt = nullptr;
	/* Used Variables */
	string str;
	string user = "dbs311_232ncc15";
	string pass = "19030228";
	string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";
	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(user, pass, constr);
		stmt = conn->createStatement();

		stmt = conn->createStatement("CREATE TABLE student (s_id NUMBER(4), name VARCHAR2(40))");
		stmt->executeUpdate();

		cout << "Table Created successfully." << endl;

		conn->terminateStatement(stmt);
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << "error";
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	return 0;
}