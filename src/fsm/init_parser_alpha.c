/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser_alpha.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:20:35 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:22:03 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	**init_args(void)
{
	char	**alphabet;

	alphabet = ft_sarradd(NULL, "R");
	alphabet = ft_sarradd(alphabet, "A");
	alphabet = ft_sarradd(alphabet, "C");
	alphabet = ft_sarradd(alphabet, "L");
	alphabet = ft_sarradd(alphabet, "pl");
	alphabet = ft_sarradd(alphabet, "sp");
	alphabet = ft_sarradd(alphabet, "sq");
	alphabet = ft_sarradd(alphabet, "cy");
	alphabet = ft_sarradd(alphabet, "tr");
	return (alphabet);
}
