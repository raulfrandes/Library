#include "Exceptions.h"

ostream& operator<<(ostream& out, const ValidExcept& except) {
	for (const auto& msg : except.message) {
		out << msg << " ";
	}
	return out;
}

ostream& operator<<(ostream& out, const RepoExcept& ex) {
	out << ex.msg;
	return out;
}


ostream& operator<<(ostream& out, const BasketExcept& ex) {
	out << ex.msg;
	return out;
}

ostream& operator<<(ostream& out, const FileExcept& ex) {
	out << ex.msg;
	return out;
}