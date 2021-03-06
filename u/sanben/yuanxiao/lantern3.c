
#include <ansi.h>
#define FILE_PATH "/u/sanben/yuanxiao/lantern3.o"
#define CARD_PATH "/u/sanben/yuanxiao/lot_card.c"

inherit ITEM;

void create()
{
        set_name(HIW"元宵灯笼" NOR, ({ "deng long", "lantern"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "这是元宵节里装点节日气愤的彩灯," +
			            "上面还写满了谜语。\n"NOR +
				HIC  "你可以用(view lantern)来查看有什么谜语。\n" +
				     "也可以用(push 题号)和(answer 答案)来猜谜语。\n"NOR);			
                set("unit", "只");
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
		{ write("你刚看过谜题，老看不晃眼吗？\n");return 1;}
	    else
		{ me->set_temp("last_view", time());}	

	    restore_object( FILE_PATH, 1 );	    

	    for (i = 1; i < 11; i++)
			{							
				if (ob->query("/ans/"+i) == 1)
				    {
 					answer += HIR"已 "NOR;					
				     }
				else
				    {
 					answer += HIG"未 "NOR;
				     }			 
				answer1 += HIY"答 "NOR;
			}		

	    if (arg == "lantern" || arg == "deng long")
		
        {			
                tell_object(me,
HIW"\n"+
"     ┏━━━━━━━━ "HIR"元宵快乐"HIW" ━━━━━━━━┓\n"+
"     ┃  ┌───欢迎参加元宵猜谜语活动───┐  ┃\n"+
"     ┃  │                                  │  ┃\n");
        tell_object(me,
"     ┃  │" + HIY"        机会多多，奖励多多！" + HIW"      │  ┃\n"+
"     ┃  │" + HIY"           快来参加吧！" + HIW"           │  ┃\n"+
"     ┃  │                                  │  ┃\n"+
"     ┃  │ 1.天没它大，人有它大(打一字)     │  ┃\n"+
"     ┃  │ 2.手电筒(打一种证件)             │  ┃\n"+
"     ┃  │ 3.菜田浇水除草(打一字)           │  ┃\n"+
"     ┃  │ 4.胸衣(打一社会现象)             │  ┃\n"+
"     ┃  │ 5 初见成效(打一非洲国家)         │  ┃\n"+
"     ┃  │ 6 四夕(打一非洲城市)             │  ┃\n"+
"     ┃  │ 7 咬一口走一步(打一工具)         │  ┃\n"+
"     ┃  │ 8 妓女罢工(打一历史用语)         │  ┃\n"+
"     ┃  │ 9 十日谈(打一字)                 │  ┃\n"+
"     ┃  │10 置之脑后(打一日用品)           │  ┃\n"+
"     ┃  │                                  │  ┃\n"+
"     ┃  │" + HBRED+ HIM"   1  2  3  4  5  6  7  8  9  10  "NOR + HIW"│  ┃\n"+
"     ┃  │  " + answer + HIW" │  ┃\n"+ 
"     ┃  │  " + answer1 + HIW" │  ┃\n");  
	tell_object(me,
"     ┃  │                                  │  ┃\n"+
HIW"     ┃  └─────────────────┘  ┃\n"+
"     ┗━━━━━━━━━━━━━━━━━━━━━┛\n"NOR);
	return 1;
        }
	    else
		return notify_fail("你要看什么？\n");
	}	

int do_push( string number )

	{    int num;
	     object me, ob;		
		
	     me = this_player();
	     ob = this_object();
	     num = atoi(number);

		if (! wizardp(me) && time() - me->query_temp("last_push_lantern") < 30)
		{ write("你刚选过题目，过30秒才能再选！\n");return 1;}
	    else
		{ me->set_temp("last_push_lantern", time());}	

		
	     if (num <= 0 || num > 10)
		{
	     	    write(HIC"你要回答第几题?\n"NOR);
		    return 1;
		}
	     else
		{   		    		    
		    restore_object( FILE_PATH, 1 );
		    if (ob->query("/ans/" + num) == 1)
		    {
			write(HIR"很抱歉，这题已经被人回答过了!\n"NOR);
			return 1;
		    }
		    else
		    {
			write(HIG"您选择了第" + num + 
				"号谜语,请接着用(answer 答案)来回答。\n"NOR);
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
		{ write("你刚回答过一次，过30秒才能再答！\n");return 1;}
	     else
		{ me->set_temp("last_answer_lantern", time());}	
	     
	     num1 = me->query_temp("answer_riddle") - 1;
	     guess = 0;
		
	     if ( num1 < 0 ) { write(HIR"请先用(push 号码)来选题号!\n"NOR);
				   return 1;}

	      restore_object( FILE_PATH, 1 );
	     if (ob->query("/ans/" + (num1 + 1)) == 1)
		    {
			write(HIR"很抱歉，您晚了一步，这题刚刚被人回答了!\n"NOR);
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
		write(HIY"您现在回答第"+ num1 + "题。\n"NOR);
		if (guess == 1) 
		{				
			ob->set("/ans/"+ num1, 1);
			save_object( FILE_PATH, 1);

			me->delete_temp("answer_riddle");	
			prize = new(CARD_PATH);
			prize->move(this_player());

			write(HBGRN"恭喜您答对了！\n"NOR);
			message_vision(HIW"只见灯龙里掉出一张" + HIG"抽奖卡"HIW +"，$N“滋溜”一下就把卡拾起，揣进裤腰带里\n" +
                                    HIW"接着贼眉鼠眼地四出张望个不停，生怕被人看见了抢走。\n"NOR, this_player());
		
		}
		else 
		{
			write(HIM"很抱歉，答错了！\n"NOR);			
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
			tell_object(me, HBMAG"数据回复初始状态！\n"NOR);
			save_object( FILE_PATH, 1 );
			return 1;
		    }
		else
		    return 0;			
	}

