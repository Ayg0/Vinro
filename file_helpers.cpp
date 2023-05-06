#include "vinro.hpp"

int	_file_D::write_file(_term &Inf){
	std::ofstream ouf(file_name + ".edit");
	std::vector<std::string> &buff = Inf.g_buff();
	size_t	w = 0, len = buff.size();
	while (w < len)
		ouf << buff[w++] << '\n';
	ouf.close();
	return 0;
}

int	_file_D::read_file(_term &Inf){
	std::ifstream inf(file_name);
	size_t	w = 0, len = Inf.get_sreen().x;
	char	tmp[len];
	std::vector<std::string> &buff = Inf.g_buff();

	if (!inf.is_open())
		return 1;
	while (inf.getline(tmp, len)){
		buff.push_back(std::string(tmp));
	}
	inf.close();
	return 0;
}
