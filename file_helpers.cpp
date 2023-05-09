#include "vinro.hpp"

int	_file_D::write_file(_term &Inf){
	std::ofstream ouf(file_name);
	std::vector<std::string> &buff = Inf.g_buff();
	size_t	w = 0, len = buff.size();
	while (w < len)
		ouf << buff[w++];
	ouf.close();
	return 0;
}

int	_file_D::read_file(_term &Inf){
	std::ifstream inf(file_name);
	size_t	len = Inf.get_sreen().x;
	std::string	tmp;
	std::vector<std::string> &buff = Inf.g_buff();

	if (!inf.is_open()){
		buff.push_back("\n");
		return 1;
	}
	while (getline(inf, tmp)){
		if (tmp.length() > len){
			buff.push_back(std::string(tmp.begin(), tmp.begin() + len));
			buff.push_back(std::string(tmp.begin() + len, tmp.end()) + "\n");
		}
		else
			buff.push_back(std::string(tmp) + "\n");
	}
	inf.close();
	if (!buff.size()){
		buff.push_back("\n");
	}
	return 0;
}
