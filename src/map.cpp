/*
	S'ASSURER QUE LA HAUTEUR ET LA LARGEUR SOIT BIEN DÉFINIS DANS MAP.TXT
*/

#include "map.h"
#include <fstream>
#include <string>
#include <iostream>


Map::Map()
{
	std::ifstream carte("map.txt");
	std::string lecture;

	std::getline(carte, lecture);

		hauteur = std::stoi(lecture);				//Ramasse la hauteur de la map dans le fichier map

	std::cout<<"Hauteur : "<<hauteur<<std::endl;

	std::getline(carte, lecture);

		largeur = std::stoi(lecture);				//Ramasse la largeur de la map dans les fichiers
	
	std::cout<<"Largeur : "<<largeur<<std::endl;


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
					std::getline(carte, lecture);
				}else if(j<largeur-1)
				{ 
					std::getline(carte, lecture, '\t');
				}
				coordonne[i][j] = std::stoi(lecture);
				
				//std::cout<<coordonne[i][j]<<" "<<std::endl;
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
}

void Map::exitPiece()
{
	coX = coXPiece;
	coY = coYPiece;
	orientation = orientationPiece;
}

void Map::printMap()
{
	for(int i=0;i<hauteur;i++)
	{
		for(int j=0;j<largeur;j++)
		{
			std::cout<<coordonne[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
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
			std::cout<<"pre"<<coX;
			coX++;
			std::cout<<"post"<<coX<<std::endl;
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

int main()
{
	Map map;
	map.printMap();
	map.setCoordonne(1,0);
	map.setOrientation(est);
	map.addCle(4);
	while(true)
	{
		char input;
		
		std::cin>>input;
		
		switch (input)
		{
		case 'p':
			std::cout<<"Coordonne X : "<<map.getCoordonneX()<<"\t Coordonne Y : "<<map.getCoordonneY()<<"\t Orientation"<<map.getOrientation()<<std::endl;
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
		map.printMap();
		std::cout<<"Coordonne X : "<<map.getCoordonneX()<<"\t Coordonne Y : "<<map.getCoordonneY()<<"\t Orientation : "<<map.getOrientation()<<std::endl;
		std::cout<<"============================================================"<<std::endl;
	}
}