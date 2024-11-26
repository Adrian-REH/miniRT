/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idxpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:32:33 by adherrer          #+#    #+#             */
/*   Updated: 2024/11/26 09:32:33 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	idxpixel(int width, int x, int y)
{
	return ((y * width * 4) + (x * 4));
}
