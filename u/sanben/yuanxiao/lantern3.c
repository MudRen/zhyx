
#include <ansi.h>
#define FILE_PATH "/u/sanben/yuanxiao/lantern3.o"
#define CARD_PATH "/u/sanben/yuanxiao/lot_card.c"

inherit ITEM;

void create()
{
        set_name(HIW"Ԫ������" NOR, ({ "deng long", "lantern"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "����Ԫ������װ��������ߵĲʵ�," +
			            "���滹д�������\n"NOR +
				HIC  "�������(view lantern)���鿴��ʲô���\n" +
				     "Ҳ������(push ���)��(answer ��)�������\n"NOR);			
                set("unit", "ֻ");
                set("value", 10000);
                set("weight", 30);
                set("material", "paper");
		  set("no_get",1);
		  set("no_drop",1);		  		  
             }	         
        setup();
}

void init()
	{
		add_action("do_view","view");
		add_action("do_push","push");
		add_action("do_answer","answer");
		add_action("do_reset","reset");
	}
		
int do_view( string arg )
	{
	    object me,ob;
	    int i;	    
	    string answer,answer1;
	    answer =" ";
	    answer1 =" ";
	    ob = this_object();	   
	    me = this_player();

	    if (! wizardp(me) && time() - me->query_temp("last_view") < 60)
		{ write("��տ������⣬�Ͽ���������\n");return 1;}
	    else
		{ me->set_temp("last_view", time());}	

	    restore_object( FILE_PATH, 1 );	    

	    for (i = 1; i < 11; i++)
			{							
				if (ob->query("/ans/"+i) == 1)
				    {
 					answer += HIR"�� "NOR;					
				     }
				else
				    {
 					answer += HIG"δ "NOR;
				     }			 
				answer1 += HIY"�� "NOR;
			}		

	    if (arg == "lantern" || arg == "deng long")
		
        {			
                tell_object(me,
HIW"\n"+
"     ������������������ "HIR"Ԫ������"HIW" ������������������\n"+
"     ��  ����������ӭ�μ�Ԫ����������������  ��\n"+
"     ��  ��                                  ��  ��\n");
        tell_object(me,
"     ��  ��" + HIY"        �����࣬������࣡" + HIW"      ��  ��\n"+
"     ��  ��" + HIY"           �����μӰɣ�" + HIW"           ��  ��\n"+
"     ��  ��                                  ��  ��\n"+
"     ��  �� 1.��û������������(��һ��)     ��  ��\n"+
"     ��  �� 2.�ֵ�Ͳ(��һ��֤��)             ��  ��\n"+
"     ��  �� 3.���ｽˮ����(��һ��)           ��  ��\n"+
"     ��  �� 4.����(��һ�������)             ��  ��\n"+
"     ��  �� 5 ������Ч(��һ���޹���)         ��  ��\n"+
"     ��  �� 6 ��Ϧ(��һ���޳���)             ��  ��\n"+
"     ��  �� 7 ҧһ����һ��(��һ����)         ��  ��\n"+
"     ��  �� 8 ��Ů�չ�(��һ��ʷ����)         ��  ��\n"+
"     ��  �� 9 ʮ��̸(��һ��)                 ��  ��\n"+
"     ��  ��10 ��֮�Ժ�(��һ����Ʒ)           ��  ��\n"+
"     ��  ��                                  ��  ��\n"+
"     ��  ��" + HBRED+ HIM"   1  2  3  4  5  6  7  8  9  10  "NOR + HIW"��  ��\n"+
"     ��  ��  " + answer + HIW" ��  ��\n"+ 
"     ��  ��  " + answer1 + HIW" ��  ��\n");  
	tell_object(me,
"     ��  ��                                  ��  ��\n"+
HIW"     ��  ��������������������������������������  ��\n"+
"     ����������������������������������������������\n"NOR);
	return 1;
        }
	    else
		return notify_fail("��Ҫ��ʲô��\n");
	}	

int do_push( string number )

	{    int num;
	     object me, ob;		
		
	     me = this_player();
	     ob = this_object();
	     num = atoi(number);

		if (! wizardp(me) && time() - me->query_temp("last_push_lantern") < 30)
		{ write("���ѡ����Ŀ����30�������ѡ��\n");return 1;}
	    else
		{ me->set_temp("last_push_lantern", time());}	

		
	     if (num <= 0 || num > 10)
		{
	     	    write(HIC"��Ҫ�ش�ڼ���?\n"NOR);
		    return 1;
		}
	     else
		{   		    		    
		    restore_object( FILE_PATH, 1 );
		    if (ob->query("/ans/" + num) == 1)
		    {
			write(HIR"�ܱ�Ǹ�������Ѿ����˻ش����!\n"NOR);
			return 1;
		    }
		    else
		    {
			write(HIG"��ѡ���˵�" + num + 
				"������,�������(answer ��)���ش�\n"NOR);
			me->set_temp("answer_riddle", num);
			return 1;
		    }
		}
	}

int do_answer(string answer)
	
	{
	    object me, ob, prize;
	    int num1, guess;		
		
	     me = this_player();
	     ob = this_object();

	     if (! wizardp(me) && time() - me->query_temp("last_answer_lantern") < 30)
		{ write("��ջش��һ�Σ���30������ٴ�\n");return 1;}
	     else
		{ me->set_temp("last_answer_lantern", time());}	
	     
	     num1 = me->query_temp("answer_riddle") - 1;
	     guess = 0;
		
	     if ( num1 < 0 ) { write(HIR"������(push ����)��ѡ���!\n"NOR);
				   return 1;}

	      restore_object( FILE_PATH, 1 );
	     if (ob->query("/ans/" + (num1 + 1)) == 1)
		    {
			write(HIR"�ܱ�Ǹ��������һ��������ոձ��˻ش���!\n"NOR);
			me->delete_temp("answer_riddle");
			return 1;
		    }

	
		switch(num1)
        {
        	case 0 :
                if (answer == "1") { guess = 1;}
                break;
        	case 1 :
                if (answer == "2") { guess = 1;}
                break;
	 	case 2 :
                if (answer == "3") { guess = 1;}
                break;
        	case 3 :
                if (answer == "4") { guess = 1;}
                break;
	 	case 4 :
                if (answer == "5") { guess = 1;}
                break;
        	case 5 :
                if (answer == "6") { guess = 1;}
                break;
	 	case 6 :
                if (answer == "7") { guess = 1;}
                break;
        	case 7 :
                if (answer == "8") { guess = 1;}
                break;
	 	case 8 :
                if (answer == "9") { guess = 1;}
                break;
        	case 9 :
                if (answer == "10") { guess = 1;}
                break;
        }
		num1 = num1 + 1;
		write(HIY"�����ڻش��"+ num1 + "�⡣\n"NOR);
		if (guess == 1) 
		{				
			ob->set("/ans/"+ num1, 1);
			save_object( FILE_PATH, 1);

			me->delete_temp("answer_riddle");	
			prize = new(CARD_PATH);
			prize->move(this_player());

			write(HBGRN"��ϲ������ˣ�\n"NOR);
			message_vision(HIW"ֻ�����������һ��" + HIG"�齱��"HIW +"��$N�����һ�¾Ͱѿ�ʰ�𣬴�����������\n" +
                                    HIW"������ü���۵��ĳ���������ͣ�����±��˿��������ߡ�\n"NOR, this_player());
		
		}
		else 
		{
			write(HIM"�ܱ�Ǹ������ˣ�\n"NOR);			
		}
		return 1;  		
	}
		
int do_reset(object me,object ob)

	{	int i;
		me = this_player();
		ob = this_object();

		if (wizardp(me))
		    { 
			for (i = 1; i < 11; i++)
			    {	
				ob->set("/ans/"+ i, 0);				
			     }
			tell_object(me, HBMAG"���ݻظ���ʼ״̬��\n"NOR);
			save_object( FILE_PATH, 1 );
			return 1;
		    }
		else
		    return 0;			
	}

