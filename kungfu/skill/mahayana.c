//mahayana.c  大乘涅磐功
inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{   
	int level;
	level = (int) me->query_skill("linji-zhuang", 1) ;
    if ( level > 200 && (int) me->query_skill("mahayana", 1) > (level + 50) )			
       return notify_fail("你的临济十二庄落后大乘涅磐功太多，需要补一补了。\n");
	
    if ((int)me->query("shen") < 0 )
       return notify_fail("你的邪气太重，无法修炼大乘涅磐功。\n");

    return 1;
}

void skill_improved(object me)
{
}
