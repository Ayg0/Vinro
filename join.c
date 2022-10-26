#include "vinro.h"

char	*ft_strjoin(char *s1, char *s2, int flag)
{
	char		*s3;
	int			i;
	int			j;
	int			k;

	if (!s1)
		return(strdup(s2));
	if (!s2)
		return(strdup(s1));
	j = strlen(s1);
	k = strlen(s2);
	s3 = (char *)calloc((j + k + 1), sizeof(char));
	if (!s3)
		return (NULL);
	i = -1;
	while (++i < j)
		s3[i] = s1[i];
	i = -1;
	while (++i < k)
		s3[i + j] = s2[i];
	if (flag <= 0 && flag != 14)
		free(s1);
	if (flag >= 0 && flag != 14)
		free(s2);
	return (s3);
}