 // snake_poison.c 
 
#include <ansi.h> 
#include <condition.h> 
 
inherit F_CLEAN_UP; 
inherit POISON; 
 
string name() { return "snake_poison"; } 
 
string chinese_name() { return "���߾綾"; } 
 
string update_msg_others() 
{ 
       return HIG "$N" HIR "ͻȻ���ڵ��ϣ�������²�ֹ��\n" NOR; 
} 
 
string update_msg_self() 
{ 
        return HIG "��Ȼ����û���һ����ľ�����е����߾綾�����ˣ�\n" NOR; 
} 
