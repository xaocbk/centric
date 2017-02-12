#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <iomanip> 

std::fstream input_file;  //входной файл
std::fstream vote_log;//лог обработки

std::string  Names[]= {"-----","Борнов","Зыков","Меркушев","Сидоров","Кошелев","Декер","Мишин","Галлюцин","Романов","Панфилов","Федосеев","Рожков","Куликов","Ардашев"
                      ,"Кононов","Зимин","Волокитин","Титов","Носов","Лукин","Дьячков","Голованов","Веселов","Харитонов"};

struct Candidate
{
  int rating;
  int id;
};

class PQueue
{
	std::vector<Candidate> _candidates;
	std::vector<Candidate*> _top;
	int _total;
  public:
	PQueue(): _total(0),_top(4, &_candidates[0]),_candidates( sizeof(Names)/sizeof(Names[0]))
        {
	  for(int i=0;i < _candidates.size() ;++i)
	  {
	    _candidates[i].id=i;
	    _candidates[i].rating=0;
	  }
	}
	void execute_ballot(int id)
	{
	    if( push(id))
	      add_to_log();
	    
	}
private:
	bool static comparator(Candidate* a, Candidate* b)
	{
	  return a->rating > b->rating;
	}
	bool push(int id)
	{
	  if( 0< id && id< _candidates.size() )
	  {

	    _total++;
	    _candidates[id].rating+=1;
	    _top[3]= &_candidates[id];
	    std::sort( _top.begin(),_top.end(), comparator);
	    std::unique(_top.begin(),_top.end() );
	    return true;
	  } 
	  else
	  {
	    vote_log<< "неправильный ID :"<< id<<'\n';
	    return false; 
	  }
    
    
  }

  void add_to_log()
  {

	vote_log<< "Обработано "<< std::setw(5)<< _total <<" бюл.: ";
	vote_log<<" (1) Кандидат № "<< std::setw(2)<< _top[0]->id <<" - "<<  Names[_top[0]->id]  <<" [" <<std::setw(2) << _top[0]->rating <<" гол.];";
	vote_log<<" (2) Кандидат № "<< std::setw(2)<< _top[1]->id <<" - "<<  Names[_top[1]->id]  <<" [" <<std::setw(2) << _top[1]->rating <<" гол.];";
	vote_log<<" (3) Кандидат № "<< std::setw(2)<< _top[2]->id <<" - "<<  Names[_top[2]->id]  <<" [" <<std::setw(2) << _top[2]->rating <<" гол.].\n";

  }
};

int main(int argc, char **argv) 
{
  
	PQueue election;
	input_file.open("ballots.xml", std::fstream::in);
	vote_log.open("log.txt", std::fstream::out);
	vote_log<< std::left;
	std::string str;
	int _first,_last; 
	while(input_file >> str)
	{
	  _first=str.find(">")+1;
	  _last=str.find("</ballot>");
	  if(_first <_last && _last!= std::string::npos)
	  {
	    int number= atoi( str.substr(_first,_last -_first).c_str()) ;
	    election.execute_ballot( number);
	  }
	  
	}
	// тесты на неправельный id
	election.execute_ballot( -11);
	election.execute_ballot( 0);
	election.execute_ballot( 25);
	//сложность функции execute_ballot - const
	input_file.close();
	vote_log.close();
	return 0;
}
 