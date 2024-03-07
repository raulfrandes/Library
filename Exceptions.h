#pragma once
#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::ostream;

class ValidExcept {
private:
	vector<string> message;
public:
	ValidExcept(const vector<string>& errors) :message{ errors } {}

	vector<string> get_msg() {
		return message;
	}

	friend ostream& operator<<(ostream& out, const ValidExcept& except);
};

ostream& operator<<(ostream& out, const ValidExcept& except);

class RepoExcept {
private:
	string msg;
public:
	RepoExcept(string m) :msg{ m } {}
	friend ostream& operator<<(ostream& out, const RepoExcept& ex);
	string get_msg() {
		return msg;
	}
};

ostream& operator<<(ostream& out, const RepoExcept& ex);

class BasketExcept {
private:
	string msg;
public:
	BasketExcept(string m) :msg{ m } {}
	friend ostream& operator<<(ostream& out, const BasketExcept& ex);
	string get_msg() {
		return msg;
	}
};

ostream& operator<<(ostream& out, const BasketExcept& ex);

class FileExcept {
private:
	string msg;
public:
	FileExcept(string m) :msg{ m } {}
	friend ostream& operator<<(ostream& out, const FileExcept& ex);
	string get_msg() {
		return msg;
	}
};

ostream& operator<<(ostream& out, const FileExcept& ex);