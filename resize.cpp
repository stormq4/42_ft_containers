/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resize.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 10:11:21 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/09/14 10:38:01 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

int main ()
{
	std::vector<int> myvector;

	// set some initial content:
	for (int i=1;i<10;i++) myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	for (int i=0;i<myvector.size();i++)
	std::cout << ' ' << myvector[i];
	std::cout << '\n';

	return 0;
}
