// rendan.c
// Modified by haiyan

#include <ansi.h> 
inherit ITEM; 

void create() 
{ 
     set_name(HIG"�ʵ�"NOR, ({"ren dan", "dan"}));
     set("unit", "��"); 
     set("long", "����һ�ŷ��ŵ���ɫ��â��ҩ�裬����ħ�ľ������۶��ɡ�\n"); 
     set("no_drop", "�������������뿪�㡣\n"); 
     set("no_sell", "�������������뿪�㡣\n"); 
     set("no_put", "�����������ܷ����Ƕ���\n"); 
     set("no_get", "�������������뿪�Ƕ���\n"); 
     set("no_steal", "�������������뿪�Ƕ���\n"); 
     set("no_beg", "�������������뿪�Ƕ���\n"); 
     set("only_do_effect", 1);
     setup(); 
} 

int do_effect(object me) 
{ 
    mapping my; 
    message_vision("$Nһ����������һ��" +HIG+ "�ʵ���\n" NOR, me); 
    my = me->query_entire_dbase();
    switch (random(5))
    {  
         case 0:  
                write(HIY"��о�ȫ��һ�����ȣ�һ���������뵤�\n"NOR); 
                me->add("max_neili", 1 + random(5));
                break;  
         case 1:  
                write(HIG"��о�ȫ��˵������������á�\n"NOR);
                my["eff_jing"] = my["max_jing"]; 
                my["jing"] = my["max_jing"]; 
                break;  
         case 2:  
                write(HIG"��о�ȫ��˵������������á�\n"NOR);
                my["eff_qi"] = my["max_qi"]; 
                my["qi"] = my["max_qi"]; 
                break;  
         case 3:
                write(HIC"��о�ζ��������\n"NOR);
                my["food"] = me->max_food_capacity(); 
                my["water"] = me->max_water_capacity(); 
                break;  
         default: 
                write(HIC"���̵�̫�죬ʲôζ��Ҳû�г�������\n"NOR);
                break;  
    } 
    destruct(this_object()); 
    return 1; 
} 

