// Modified by haiyan

#include <ansi.h> 
inherit ITEM; 

void create() 
{ 
     set_name( HIY"��ֽ"NOR, ({ "fu zhi" })); 
     set_weight(20); 
     if( clonep() ) 
         set_default_object(__FILE__); 
     else
     { 
         set("unit", "��"); 
         set("no_put", 1);
         set("no_sell", 1);
         set("long", "����һ�ŵ�ʿ��������ħ׽��ķ�ֽ�����滭��һЩ��ֵĺ�ɫ���š�\n"); 
     } 
     setup(); 
} 

