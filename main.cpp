#include <iostream>
#include <xlnt/xlnt.hpp>
#include <fstream>

void printcell(std::ofstream &outfile, std::string s)
{
  int nondigit = 0;
  for (int i = 0; i < s.length(); i++) {
    char c = s[i];
    if ('0' <= c && c <= '9') ;
    else nondigit = 1;
  }
  if (nondigit) {
    outfile << "\"" << s << "\"";
  } else {
    outfile << s;
  }
}

void dump(std::string s, xlnt::worksheet &sheet)
{
  std::string fn = s + ".csv";
  std::ofstream outfile (fn);

   std::clog << fn << "\n";
  
  for (auto row : sheet.rows(false)) 
    { 
      for (auto cell : row) 
	{
	  xlnt::column_t::index_t i = cell.column_index();
	  //	  printf("%d:%ld\n", i, row.length() 	  );
	  
	  printcell(outfile, cell.to_string());

	  
	  if (i < row.length())
	    outfile << ",";
	}
      outfile << std::endl;      
    }

  outfile.close();
}


int main(int ac, char **av)
{
  xlnt::workbook wb;
  int i;
  char *fn = 0;
  
  for (i = 1; i < ac; i++) {
    if (av[i][0] == '-') continue;
    else {
      fn = av[i];
      break;
    }
  }
  if (fn == 0) {
    std::cout << "no file\n";
  }
  
  wb.load(fn);

  #if 0
  auto ws = wb.active_sheet();
  std::clog << "Processing spread sheet" << std::endl;
  for (auto row : ws.rows(false)) 
    { 
      for (auto cell : row) 
	{ 
	  std::clog << cell.to_string() << std::endl;
	}
    }
  std::clog << "Processing complete" << std::endl;
  #endif

  for (auto itr = wb.begin(); itr != wb.end(); itr++) {
    xlnt::worksheet sheet = *itr;
    dump(sheet.title(), sheet);
  }
  
  return 0;
}
