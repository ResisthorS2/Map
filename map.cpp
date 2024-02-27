/*
	S'ASSURER QUE LA HAUTEUR ET LA LARGEUR SOIT BIEN DÉFINIS DANS MAP.TXT
*/

#include "map.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

Map::Map(const string& fileName)
{
	ifstream carte(fileName);
	string lecture;

	getline(carte, lecture);

		hauteur = stoi(lecture);				//Ramasse la hauteur de la map dans le fichier map

	cout<<"Hauteur : "<<hauteur<<endl;

	getline(carte, lecture);

		largeur = stoi(lecture);				//Ramasse la largeur de la map dans les fichiers
	
	cout<<"Largeur : "<<largeur<<endl;


	coordonne = new int*[hauteur];					//Cree le tableau des coordonne de cases de la map
	for (int i = 0; i < hauteur; ++i) 
	{
		coordonne[i] = new int[largeur];
	}

		for(int i=0;i<hauteur;i++)					//Assigne le fichier de map au tableau coordonne
		{
			for(int j=0;j<largeur;j++)
			{
				if(j==largeur-1)
				{
					getline(carte, lecture);
				}else if(j<largeur-1)
				{ 
					getline(carte, lecture, '\t');
				}
				coordonne[i][j] = stoi(lecture);
				
				//cout<<coordonne[i][j]<<" "<<endl;
			}
	}

for(int i=0;i<maxRoom;i++)
{	
	cle[i]=0;
}

}

Map::~Map()
{
	for (int i = 0; i < hauteur; ++i) 
	{
    	delete[] coordonne[i];
	}

delete[] coordonne;

}

void Map::setCoordonne(int x, int y)
{
	coX=x;

	coY=y;
}

void Map::enterPiece()
{
	coXPiece=coX;
	coYPiece=coY;
	orientationPiece=orientation;
	etatPiece=true;
}

void Map::exitPiece()
{
	coX = coXPiece;
	coY = coYPiece;
	orientation = orientationPiece;
	etatPiece= false;
}

bool Map::printCase(int x, int y)
{
	if(x==coX&&y==coY)
	{
		char charOrientation;
		switch (orientation)
		{
		case nord:
			charOrientation='N';
			break;
		
		case est:
			charOrientation='E';
			break;

		case sud:
			charOrientation='S';
			break;

		case ouest:
			charOrientation='O';
			break;

		default:
			charOrientation='X';
			break;
		}
		
		cout<<"["<<" "<<"\033[34m"<<charOrientation<<"\033[0m"<<" "<<"]"<<" ";
		return true;

	}
	if(coordonne[y][x]==1)
	{
		cout<<"["<<" "<<" "<<" "<<"]"<<" ";
		return true;
	}
	if(coordonne[y][x]==3)
	{
		cout<<"["<<" "<<"I"<<" "<<"]"<<" ";
		return true;		
	}
	if(coordonne[y][x]==2)
	{
		cout<<"["<<" "<<"P"<<" "<<"]"<<" ";
		return true;
	}
	if(coordonne[y][x]>3)
	{
		cout<<"["<<" "<<coordonne[y][x]<<" "<<"]"<<" ";	
		return true;
	}else cout<<"      ";
	return true;
}

void Map::printMap()
{
	for(int i=0;i<hauteur;i++)
	{
		for(int j=0;j<largeur;j++)
		{
			printCase(j,i);
		}
		cout<<endl;
	}
	cout<<endl;
	string orientationPrint;
	switch (orientation)
	{
	case nord:
		orientationPrint="Nord";
		break;
	case sud:
		orientationPrint="Sud";
		break;
	case est:
		orientationPrint="Est";
		break;
	case ouest:
		orientationPrint="Ouest";
		break;
	default:
		orientationPrint="erreur";
		break;
	}
	cout<<"Coordonne X : "<<getCoordonneX()<<"\t Coordonne Y : "<<getCoordonneY()<<"\t Orientation : "<<orientationPrint<<endl;
		cout<<"============================================================"<<endl;
}

int Map::getCoordonneX()
{
	return coX;
}

int Map::getCoordonneY()
{
	return coY;
}

int Map::getOrientation()
{
	return orientation;
}

void Map::addCle(int index)
{
	cle[index]=index;
}

void Map::removeCle(int index)
{
	cle[index]=0;
}

bool Map::verifCle(int index)
{
	if(index==cle[index])
	{
		return true;
	} else return false;
}

bool Map::moveUp()
{
	switch (orientation)
	{
	case nord:
		if(coY==0)		//Il est dans le top de la map et ne peux pas monter
		{
			return false;
		}

		if(coordonne[coY-1][coX]==1)	//Il a une case couloir devant lui
		{
			coY--;
			return true;
		}

		if(coordonne[coY-1][coX]==3)	//Il a une case intersection devant lui
		{
			if(coY==1)					//Il n'y a pas de case devant la case intersection
			{
				return false;
			}
			if(coordonne[coY-2][coX]==1||coordonne[coY-2][coX]==2)	//Il y a une case couloir devant la case interception
			{
				coY--;
				coY--;
				return true;
			}

			if(coordonne[coY-2][coX]>3)	//Il y a une case couloir devant la case interception
			{
				if(verifCle(coordonne[coY-2][coX])==true)
				{
				enterPiece();
				coY--;
				coY--;
				return true;
				}
			}


			if(coordonne[coY-2][coX]==0)	//Il n'y a pas de case marchable devant la case intersection
			{
				return false;
			}			
			return true;
		}
		return false;
		break;


	case sud:
		if(coY==(hauteur-1))		//Il est dans le bas de la map et ne peux pas descendre
		{
			return false;
		}

		if(coordonne[coY+1][coX]==1||coordonne[coY+1][coX]==2)	//Il a une case couloir devant lui
		{
			coY++;
			return true;
		}

		if(coordonne[coY+1][coX]==3)	//Il a une case intersection devant lui
		{
			if(coY==hauteur-2)					//Il n'y a pas de case devant la case intersection
			{
				return false;
			}
			if(coordonne[coY+2][coX]==1||coordonne[coY+2][coX]==2)	//Il y a une case couloir devant la case interception
			{
				coY++;
				coY++;
				return true;
			}
			if(coordonne[coY+2][coX]>3)	//Il y a une case couloir devant la case interception
			{
				if(verifCle(coordonne[coY+2][coX])==true)
				{
				enterPiece();
				coY++;
				coY++;
				return true;
				}
			}
			if(coordonne[coY+2][coX]==0)	//Il n'y a pas de case marchable devant la case intersection
			{
				return false;
			}
		}		
		return false;
		break;

	case est:
		if(coX==(largeur-1))		//Il est tout à droite de la map de la map et ne peux pas monter
		{
			return false;
		}
		
		if(coordonne[coY][coX+1]==1||coordonne[coY][coX+1]==2)	//Il a une case couloir devant lui
		{
			cout<<"pre"<<coX;
			coX++;
			cout<<"post"<<coX<<endl;
			return true;
		}

		if(coordonne[coY][coX+1]==3)	//Il a une case intersection devant lui
		{
			if(coX==largeur-2)					//Il n'y a pas de case devant la case intersection
			{
				return false;
			}
			if(coordonne[coY][coX+2]==1||coordonne[coY][coX+2]==2)	//Il y a une case couloir devant la case interception
			{
				coX++;
				coX++;
				return true;
			}

			if(coordonne[coY][coX+2]==0)	//Il n'y a pas de case marchable devant la case intersection
			{
				return false;
			}			

			if(coordonne[coY][coX+2]>3)
			{
				if(verifCle(coordonne[coY][coX+2])==true)
				{
					enterPiece();
					coX++;
					coX++;
					return true;
				}	else return false;
			}
		}
		return false;
		break;
		
	case ouest:

		if(coX==0)		//Il est tout à gauche de la map de la map et ne peux pas monter
		{
			return false;
		}

		if(coordonne[coY][coX-1]==1||coordonne[coY][coX-1]==2)	//Il a une case couloir devant lui
		{
			coX--;
			return true;
		}

		if(coordonne[coY][coX-1]==3)	//Il a une case intersection devant lui
		{
			if(coX==1)					//Il n'y a pas de case devant la case intersection
			{
				return false;
			}
			if(coordonne[coY][coX-2]==1||coordonne[coY][coX-2]==2)	//Il y a une case couloir devant la case interception
			{
				coX--;
				coX--;
				return true;
			}
			if(coordonne[coY][coX-2]>2)
			{
				if(verifCle(coordonne[coY][coX-2])==true)
				{
					enterPiece();
					coX--;
					coX--;
					return true;
				} else return false;
			}
			if(coordonne[coY][coX-2]==0)	//Il n'y a pas de case marchable devant la case intersection
			{
				return false;
			}			
		}
		return true;
		break;				

	default:
		return false;
		break;
	}
	return false;

}

bool Map::moveDown()
{
	switch (orientation)
	{
	case nord:
		orientation=sud;
		return true;
		break;

	case est:
		orientation=ouest;
		return true;
		break;

	case sud:
		orientation=nord;
		return true;
	case ouest:
		orientation=est;
		return true;

	default:
		return false;
		break;
	}
	return false;
}

bool Map::moveRight()
{

		switch (orientation)
		{
		case nord:

			if(coordonne[coY-1][coX]==2)				//si il y a une piece
			{
				if(coX==(largeur-1))					//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}
				if(verifCle(coordonne[coY-1][coX+1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY--;
					coX++;
					orientation = est;
					return true;
				} else return false;
			} else if(coordonne[coY-1][coX]==3) 		//Arrive à une intersection
				{
					if(coX == largeur-1)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY-1][coX+1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si iil peut rentrer
					{
						if(verifCle(coordonne[coY-1][coX+1]))	
						{
							enterPiece();
							coY--;
							coX++;
							orientation = est;
							return true;
						} else return false;	
					}
					if(coordonne[coY-1][coX+1]==1||coordonne[coY-1][coX+1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY--;
						coX++;
						orientation = est;
						return true;
					}

				} else return false;

			break;

		case sud:

			if(coordonne[coY+1][coX]==2)				//si il y a une piece
			{
				if((coX)==0)							//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}				
				if(verifCle(coordonne[coY+1][coX-1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY++;
					coX--;
					orientation = ouest;
					return true;
				} else return false;
			} else if(coordonne[coY+1][coX]==3) 		//Arrive à une intersection
				{
					if(coX == 0)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY+1][coX-1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si iil peut rentrer
					{
						if(verifCle(coordonne[coY+1][coX-1]))	
						{
							enterPiece();
							coY++;
							coX--;
							orientation = ouest;
							return true;
						} else return false;	
					}
					if(coordonne[coY+1][coX-1]==1||coordonne[coY+1][coX-1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY++;
						coX--;
						orientation = ouest;
						return true;
					}

				} else return false;

			break;

		case est:

			if(coordonne[coY][coX+1]==2)				//si il y a une piece
			{
				if(coY== (hauteur -1))							//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}				
				if(verifCle(coordonne[coY+1][coX+1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY++;
					coX++;
					orientation = sud;
					return true;
				} else return false;
			} else if(coordonne[coY][coX+1]==3) 		//Arrive à une intersection
				{
					if(coY == hauteur-1)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY+1][coX+1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si iil peut rentrer
					{
						if(verifCle(coordonne[coY+1][coX+1]))	
						{
							enterPiece();
							coY++;
							coX++;
							orientation = sud;
							return true;
						} else return false;	
					}
					if(coordonne[coY+1][coX+1]==1||coordonne[coY+1][coX+1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY++;
						coX++;
						orientation = sud;
						return true;
					}

				} else return false;

			break;
		
		case ouest:

			if(coordonne[coY][coX-1]==2)				//si il y a une piece
			{
				if(coY== 0)							//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}				
				if(verifCle(coordonne[coY-1][coX-1]))	//Verifie s'il peut rentrer
				{
					coY--;
					coX--;
					orientation = nord;
					return true;
				} else return false;
			} else if(coordonne[coY][coX-1]==3) 		//Arrive à une intersection
				{
					if(coY == 0)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY-1][coX-1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si il peut rentrer
					{
						if(verifCle(coordonne[coY-1][coX-1]))	
						{
							coY--;
							coX--;
							orientation = nord;
							return true;
						} else return false;	
					}
					if(coordonne[coY-1][coX-1]==1||coordonne[coY-1][coX-1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY--;
						coX--;
						orientation = nord;
						return true;
					}

				} else return false;

			break;

		default:
		return false;
			break;
		}	

	return false;
}

bool Map::moveLeft()
{
		switch (orientation)
		{
		case nord:

			if(coordonne[coY-1][coX]==2)				//si il y a une piece
			{
				if(coX==0)					//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}
				if(verifCle(coordonne[coY-1][coX-1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY--;
					coX--;
					orientation = ouest;
					return true;
				} else return false;
			} else if(coordonne[coY-1][coX]==3) 		//Arrive à une intersection
				{
					if(coX == 0)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY-1][coX-1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si iil peut rentrer
					{
						if(verifCle(coordonne[coY-1][coX-1]))	
						{
							enterPiece();
							coY--;
							coX--;
							orientation = ouest;
							return true;
						} else return false;	
					}
					if(coordonne[coY-1][coX-1]==1||coordonne[coY-1][coX-1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY--;
						coX--;
						orientation = ouest;
						return true;
					}

				} else return false;

			break;

		case sud:

			if(coordonne[coY+1][coX]==2)				//si il y a une piece
			{
				if((coX)== largeur - 1)							//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}				
				if(verifCle(coordonne[coY+1][coX+1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY++;
					coX++;
					orientation = est;
					return true;
				} else return false;
			} else if(coordonne[coY+1][coX]==3) 		//Arrive à une intersection
				{
					if(coX == largeur - 1)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY+1][coX+1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si iil peut rentrer
					{
						if(verifCle(coordonne[coY+1][coX+1]))	
						{
							enterPiece();
							coY++;
							coX++;
							orientation = est;
							return true;
						} else return false;	
					}
					if(coordonne[coY+1][coX+1]==1||coordonne[coY+1][coX+1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY++;
						coX++;
						orientation = est;
						return true;
					}

				} else return false;

			break;

		case est:

			if(coordonne[coY][coX+1]==2)				//si il y a une piece
			{
				if(coY== 0)							//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}				
				if(verifCle(coordonne[coY-1][coX+1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY--;
					coX++;
					orientation = nord;
					return true;
				} else return false;
			} else if(coordonne[coY][coX+1]==3) 		//Arrive à une intersection
				{
					if(coY == 0)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY-1][coX+1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si iil peut rentrer
					{
						if(verifCle(coordonne[coY-1][coX+1]))	
						{
							enterPiece();
							coY--;
							coX++;
							orientation = nord;
							return true;
						} else return false;	
					}
					if(coordonne[coY-1][coX+1]==1||coordonne[coY-1][coX+1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY--;
						coX++;
						orientation = nord;
						return true;
					}

				} else return false;

			break;
		
		case ouest:

			if(coordonne[coY][coX-1]==2)				//si il y a une piece
			{
				if(coY== hauteur - 1)							//Verifie si l'intersection est sur le bord de la map
				{
					return false;
				}				
				if(verifCle(coordonne[coY+1][coX-1]))	//Verifie s'il peut rentrer
				{
					enterPiece();
					coY++;
					coX--;
					orientation = sud;
					return true;
				} else return false;
			} else if(coordonne[coY][coX-1]==3) 		//Arrive à une intersection
				{
					if(coY == hauteur - 1)				//Verifie si l'intersection est sur le bord de la map
					{
						return false;
					}
					if(coordonne[coY+1][coX-1]>3)		//Verifie si c'est une pièce à cote de l'intersection et verifie si il peut rentrer
					{
						if(verifCle(coordonne[coY+1][coX-1]))	
						{
							enterPiece();
							coY++;
							coX--;
							orientation = sud;
							return true;
						} else return false;	
					}
					if(coordonne[coY+1][coX-1]==1||coordonne[coY+1][coX-1]==2)		//Verifie si c'est une case couloir à l'intersection
					{
						coY++;
						coX--;
						orientation = sud;
						return true;
					}

				} else return false;

			break;
			

		default:
		return false;
			break;
		}	
	
	return false;
}

void Map::setOrientation(int SETorientation)
{
	orientation=SETorientation;
}

bool Map::isInPiece()
{
	if(etatPiece==true)
	{
		return true;
	} else return false;
}

int main()
{
	Map map("map.txt");
	map.setCoordonne(1,0);
	map.setOrientation(est);
	map.addCle(4);
	map.printMap();
	while(true)
	{
		char input;
		
		cin>>input;
		
		if(map.isInPiece()==true)
		{
			if(input=='s')
			{
				map.exitPiece();
			}
		}
		if(map.isInPiece()==false)
		{
			switch (input)
			{
			case 'p':
				cout<<"Coordonne X : "<<map.getCoordonneX()<<"\t Coordonne Y : "<<map.getCoordonneY()<<"\t Orientation"<<map.getOrientation()<<endl;
				break;
			case 'w':
				map.moveUp();
				break;
			
			case 'a':
				map.moveLeft();
				break;
			
			case 's':
				map.moveDown();
				break;
			case 'd':
				map.moveRight();	
				break;
			}
		}
		map.printMap();
	}
}
