#include "../main.h"

char	**init_args()
{
	char	**alphabet;

	alphabet = ft_sarradd(NULL, "R"); //posicion 0 Resolution
	alphabet = ft_sarradd(alphabet, "A");//posicion 1 Ambient
	alphabet = ft_sarradd(alphabet, "C");//posicion 2	camara
	alphabet = ft_sarradd(alphabet, "L");//posicion 2	Light
	alphabet = ft_sarradd(alphabet, "pl");//posicion 4 Plane
	alphabet = ft_sarradd(alphabet, "sp"); //posicion 5 Sphere
	alphabet = ft_sarradd(alphabet, "sq");//posicion 6 Square
	alphabet = ft_sarradd(alphabet, "cy");//posicion 7 Cylinder
	alphabet = ft_sarradd(alphabet, "tr");//posicion 8 Triangle
	return (alphabet);
}
