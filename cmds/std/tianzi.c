// tianzi.c
// by SmallFish  in  1/22/2002  in JDMR

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{	
	object ob;
	mapping mine;
	string line;
	int basic_data;

//	me = this_player();

       ob = me;
       if (!arg)
	       ob = me;
       else if (me->query("born_tianzi") < 1) write(HIW"������ʶ��Ѿ��������ˣ�\n"NOR);
       else
       {
              switch(arg)
              {
                    case "����":
                            if (me->query("int") >= 30) 
                                    write(HIW"������������Ѿ��ﵽ��30���޷��ٷ�������\n"NOR);
                            else
                            {
                                    me->add("int",1);
                                    me->add("born_tianzi",-1);
                                    write(HIW"�㽫һ�����ʷ�������ԡ�\n"NOR);
                            }
                            break;
                    case "����":
                            if (me->query("str") >= 30) 
                                    write(HIW"������������Ѿ��ﵽ��30���޷��ٷ�������\n"NOR);
                            else
                            {
                                    me->add("str",1);
                                    me->add("born_tianzi",-1);
                                    write(HIW"�㽫һ�����ʷ����������\n"NOR);
                            }
                            break;
                    case "��":
                            if (me->query("dex") >= 30) 
                                    write(HIW"����������Ѿ��ﵽ��30���޷��ٷ�������\n"NOR);
                            else
                            {
                                    me->add("dex",1);
                                    me->add("born_tianzi",-1);
                                    write(HIW"�㽫һ�����ʷ��������\n"NOR);
                            }
                            break;
                    case "����":
                            if (me->query("con") >= 30) 
                                    write(HIW"�����������Ѿ��ﵽ��30���޷��ٷ�������\n"NOR);
                            else
                            {
                                    me->add("con",1);
                                    me->add("born_tianzi",-1);
                                    write(HIW"�㽫һ�����ʷ�������ǡ�\n"NOR);
                            }
                            break;
                    default:
                            write(HIW"��ֻ�ܰ����ʷ���������������ԡ����ǡ������������ԡ�\n"NOR);
                            break;
              }
	}

	mine = ob->query_entire_dbase();
	line = sprintf("\n-------��������-------\n");
	line += sprintf(
			" ������[%s]  ���ԣ�[%s]  ���ǣ�[%s]  ����[%s]\n\n", 
			sprintf("%3d",mine["str"]),
			sprintf("%3d",mine["int"]),
			sprintf("%3d",mine["con"]),
			sprintf("%3d",mine["dex"]));
	line += sprintf("-------��������-------\n");
	line += sprintf(
			" ������[%s]  ���ԣ�[%s]  ���ǣ�[%s]  ����[%s]\n\n", 
			sprintf("%3d",ob->query_str()),
			sprintf("%3d",ob->query_int()),
			sprintf("%3d",ob->query_con()),
			sprintf("%3d",ob->query_dex()));
	line += sprintf(HIC"-------ħ������������ǣ�%s\n\n"NOR, sprintf("%3d",ob->query("con_improve_time")));

	basic_data = mine["str"] + mine["int"] + mine["con"] + mine["dex"] + me->query("born_tianzi");
	if(basic_data > (80 + (int)ob->query("con_improve_time")))
 	  line += sprintf(HIY "���������쳣, %3d - 80 = %3d\n\n" NOR,basic_data,(basic_data-80));
	  line += sprintf(HIY "ʣ��ɷ������ʣ�%3d\n\n"NOR,me->query("born_tianzi"));		
	write(line); 

	return 1;
}



