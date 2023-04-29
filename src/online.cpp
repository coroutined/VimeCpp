#include "online.hpp"


Online::Online(const Json::Value &object): Online() {
	if(object.empty()) { return; }

	total = object["total"].asUInt();
	for(std::string &key: object["separated"].getMemberNames()) {
		separated[key] = object["separated"][key].asUInt();
	}
}

Online::Online(Online &&old) noexcept:
	total(std::move(old.total)),
	separated(std::move(old.separated)) {}

std::ostream &operator<<(std::ostream &os, const Online &rval) {
	os << rval.toString();
	return os;
}

std::string Online::toString() const {
	return format(R"({"total":{0},"separated":{1}})", total, ::toString(separated));
}


Stream::Stream(const Json::Value &object): Stream() {
	if(object.empty()) { return; }

	title = object["title"].asString();
	owner = object["owner"].asString();
	viewers = object["viewers"].asUInt();
	url = object["url"].asString();
	duration = object["duration"].asUInt();
	platform = object["platform"].asString();
	user = object["user"];
}

Stream::Stream(Stream &&old) noexcept:
	title(std::move(old.title)),
	owner(std::move(old.owner)),
	viewers(std::move(old.viewers)),
	url(std::move(old.url)),
	duration(std::move(old.duration)),
	platform(std::move(old.platform)),
	user(std::move(old.user)) {}

std::ostream &operator<<(std::ostream &os, const Stream &rval) {
	os << rval.toString();
	return os;
}

std::string Stream::toString() const {
	return format(R"({"title":{0},"owner":{1},"viewers":{2},"url":{3},)"
				  R"("duration":{4},"platform":{5},"user":{6}})",
				  ::toString(title, true), ::toString(owner, true), viewers, 
				  ::toString(url, true), duration, ::toString(platform, true), 
				  user.toString());
}


OnlineStaff::OnlineStaff(const Json::Value &object): OnlineStaff() {
	if(object.empty()) { return; }

	user = object;
	online = object["online"];
}

OnlineStaff::OnlineStaff(OnlineStaff &&old) noexcept:
	user(std::move(old.user)),
	online(std::move(old.online)) {}

std::ostream &operator<<(std::ostream &os, const OnlineStaff &rval) {
	os << rval.toString();
	return os;
}

std::string OnlineStaff::toString() const {
	std::string userString = user.toString();
	return userString.substr(0, userString.length() - 1) + 
		   format(R"(,"online":{0}})", online.toString());
}