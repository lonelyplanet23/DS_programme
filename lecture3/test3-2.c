#include<stdio.h>

struct stu{

	int num;

	float TotalScore;

};

void f(struct stu p)

{

	struct stu s[2]={{20044,550},{20045,537}};

	p.num=s[1].num;

	p.TotalScore=s[1].TotalScore;

}

int main()

{

	struct stu s[2]={{20041,703},{20042,580}};

	f(s[0]);

	printf("%d %3.0f\n",s[0].num,s[0].TotalScore);

	return 0;

}