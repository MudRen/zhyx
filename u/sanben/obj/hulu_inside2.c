// �Ͻ��«�ڲ�
#include <room.h>
#include <ansi.h>

//inherit ROOM;
inherit CREATE_CHAT_ROOM;
int is_chat_room() { return 1; } 


#define MASTER "sanben"
#define HULU_INSIDE  "/u/sanben/obj/hulu_inside"

string look_paizi();

void create()
{
        set("short",NOR YEL"�Ͻ��«�ڲ�"NOR);
        set("long", YEL"\n"
"�������Ͻ��«���ڲ������ܿյ����ģ�ʹ�����������ʴӵĸо���\n"
"��е���ѹ�֣�����Ͽ��뿪���������ôҲ�Ҳ��ų��ڡ���˵\n"
"Ҫ�뿪����Ψһ�İ취���ǿ����Խ�³�һ����«�����趨����λ\n"
"�������ڹ�����Կ������ӡ�\n"
"    �Ա���һ������(paizi)��\n"NOR);
        set("no_fight", 1);
        set("item_desc", ([
                "paizi" : (: look_paizi :),
        ]));
}

void init()
{
        object me = this_player();

        if ( me->query("id") != MASTER )
        {
           me->set("startroom", HULU_INSIDE);
        add_action("do_suicide", "suicide");
        add_action("do_drop", "drop");
        add_action("do_give", "give");

        add_action("no_go", "rideto");
        add_action("no_go", "rideto1");
        add_action("no_go", "miss");
        add_action("no_go", "flyup");

        add_action("no_go", "trans");
        add_action("no_go", "recall");

        add_action("do_quit", "quit");
        add_action("do_quit", "exit");
        //wiz�ķ���Ҳ��ʧ�ˣ�����
        add_action("no_power", "home");
        add_action("no_power", "goto");
        add_action("no_power", "flyto");

        add_action("no_power", "more");
        add_action("no_power", "edit");
        add_action("no_power", "ls");
        add_action("no_power", "cd");
        add_action("no_power", "rm");
        add_action("no_power", "mv");
        add_action("no_power", "cp");

        add_action("no_power", "kickout");
        add_action("no_power", "purge");
        add_action("no_power", "summon");
        add_action("no_power", "promote");
        add_action("no_power", "throw");
        add_action("no_power", "dest");
        add_action("no_power", "auth");
        add_action("no_power", "free");
        add_action("no_power", "grant");
        add_action("no_power", "update");
        add_action("no_power", "data");
        add_action("no_power", "info");
        add_action("no_power", "call");
        add_action("no_power", "clone");
        add_action("no_power", "dual");
        add_action("no_power", "smash");
        add_action("no_power", "possess");
        add_action("no_power", "clear");


        add_action("do_guess", "guess");
        add_action("do_giveup", "giveup");
        message_vision(HIY"ֻ�����E����һ����$N��װ���˺�«�\n"NOR,
                                                this_player());
        call_other(HULU_INSIDE, "set_number", me);
        }
}


int do_suicide()
{
        write(HIB"��Ҫ��ô��������α���Ѱ�̽��أ�\n"NOR);
        return 1;
}

int do_give()
{
        write(HIG"���ﲻ�ܸ�������\n"NOR);
        return 1;
}

int do_drop()
{
        write(HIG"���ﲻ�����Զ�����\n"NOR);
        return 1;
}

//������������ܣ�

int no_go()
{
        write(YEL"�Ͻ��«��������˵�߾��ߣ�\n"NOR);
        return 1;
}


int do_quit()
{
        write(HIR"�����ھ����˳���Ϸ�»����߽������������"
              "���Ի��Ǳ�quit�˰ɣ�\n"NOR);
        return 1;
}

//��ʦҲ�ܲ��ˣ� ���� (��Ȼ��������Ϲ����,keke)

int no_power()
{
        write(HIC"���������������ʦҲû�����ˣ��������ˣ�������\n"NOR);
        return 1;
}

string look_paizi()
{
    string msg,*result,*number;
    object me;
    int i;

    me = this_player();

    msg = HIG"\n��«���԰ף���ʵ�ұ�����̫���Ͼ����Ƴ����ķ�����������\n"
             "�ڱ���Ǵ���в�֣�����ֻ����������������������δ������\n"
             "�ǻᾡ��������ġ�ֻҪ���ܲ����Ҹ����趨�õ�һ�������\n"
             "��λ���Ϳ��Գ�ȥ�ˡ�\n"
             "�����λ���ĸ�λ�ϵ����ֶ����ظ����Ҷ���Ϊ 0�����а˴�\n"
             "���ᣬ�˴λ��²��еĻ��ͻỻ��һ���������¿�ʼ�ٲ¡���\n"
             "����guess xxxx ÿ��һ���Ҿͻ����һ����ʾ��\n"NOR +
             HIR"A"NOR + HIY"��ʾλ��Ҳ�ԣ�����Ҳ�ԡ�" NOR +
             HIR"B"NOR + HIY"��ʾ���ֶ��˵���λ�����ԡ�\n"NOR +
             HIR"�²����Ļ���ֻ�����Ǵ���Ͷ��(giveup)����\n"NOR;

    msg += HIW"\n�����ڻ���" + chinese_number( 8 - me->query("hulu/guess/time"))
           + "�λ����������֡�\n"NOR;

 /*   if ( me->query("hulu/guess/") )
    {
       result = me->query("hulu/guess/result/");
       number = me->query("hulu/guess/number/");

       msg += HIY"�����ڲ¹������ּ�¼�ǣ�\n"NOR;
       for ( i = 0; i < sizeof(result); i++)
       {
          msg += HIG + me->query("hulu/guess/number/"+ i) + "     ";
          msg += me->query("hulu/guess/result/"+ i) + "\n"NOR;
       }

    }      */
    return msg + "\n";
}

void set_number(object me)
{
   int i,ii,x,y;

   me->delete("hulu");
   for (i = 0; i < 4; i++)
   {
      x = random(9) + 1;
      y = 0;

      if ( sizeof(me->query("hulu/number")) > 0 )
      {
         for (ii = 0; ii < sizeof(me->query("hulu/number")); ii++)
         {
             if (me->query("hulu/number/" + ii) == x)
             {
               y = 1;
             }
         }
      }
      if (y == 0) me->set("hulu/number/" + i,x);
      else i = i - 1;
   }
}

int do_guess(string arg)
{
   int num, num1, num2, num3, num4, i, ii, a, b, *num_arr, exp, pot, tihui;
   object me;
   string number,msg;
write("��������������,�������ȥ��!\n");
return 1;
   num_arr = allocate(4);
   num = atoi(arg);
   me = this_player();
   number = "";

   if ( time() - me->query("hulu/last_guess") < 5 )
   {
       return notify_fail("����ô�µ���ô�죬�ǲ����û����˵ģ�\n");
   }

   if (! arg )
   return notify_fail("��Ҫ���ĸ����֣�\n");

   if ( sizeof(arg) != 4 || num == 0 || num < 1000 || num > 9999)
   return notify_fail("���һ����λ������\n");

   num1 = num / 1000;
   num2 = (num - num1 * 1000) / 100;
   num3 = (num - num1 * 1000 - num2 * 100)/ 10;
   num4 = (num - num1 * 1000 - num2 * 100 - num3 * 10);

   if ( num1 == num2 || num1 == num3 || num1 == num4 || num2 == num3 ||
        num2 == num4 || num3 == num4)

   return notify_fail("�����λ����λ�����ظ���������µ�����Ҳ���ظ���\n");

   num_arr[0] = num1;
   num_arr[1] = num2;
   num_arr[2] = num3;
   num_arr[3] = num4;

   for (i = 0; i < 4; i++)                //���ж��м���A
   {
       if (me->query("hulu/number/" + i) == num_arr[i])
       {
          a += 1;
       }

   }

   for (i = 0; i < 4; i++)                //���ж��м���B
   {
       for (ii = 0; ii < 4; ii++)
       {
           if (me->query("hulu/number/" + i) == num_arr[ii])
           {
              b += 1;
           }
       }
   }
   b = b - a;    

   me->set("hulu/guess/result/" + me->query("hulu/guess/time"),a +"A"+ b +"B");
   me->set("hulu/guess/number/" + me->query("hulu/guess/time"),
           num1+""+num2+""+num3+""+num4);
   me->add("hulu/guess/time", 1);
   me->set("hulu/last_guess",time());
   if ( a == 4 )
   {
      me->set("startroom", "/d/city/kedian/");
      tell_object(me,HIW"�ۣ���ô��������У���̫�����ˣ�û���𰸾���:"NOR
                     HIR + num + NOR HIY
                    "\n���������������������Ͻ��«Ҳ���㲻ס�ˣ�\n"NOR);

    /*  exp = 9000 + random(1000);
      pot = 5000 + random (500);
      tihui = 1000 + random(200);  */

      exp = 1000 + random(500);
      pot = 500 + random (300);
      tihui = 200 + random(100);

      me->add("combat_exp", exp);
      me->add("potential", pot);
      me->add("experience", tihui);

      message_vision(HIC"ֻ����«��ͻȻ���˿�����$Nವ�һ�����˳�ȥ��\n"NOR,
                     this_player());

      tell_object( me, HIG"ͨ������������̣�������"NOR HIR +
                   chinese_number(exp) + HIG"�㾭�飬\n"NOR HIW +
                   chinese_number(pot) + NOR HIG"��Ǳ���Լ�"HIY +
                   chinese_number(tihui) + HIG"��ʵս��ᡣ\n"NOR);
      me->delete("hulu");


      me->move("/d/city/kedian");
   }
   else
   {
   if (me->query("hulu/guess/time") < 8 )
      {
        /*   write(HIC"������Ĵ����У�"NOR HIR+ a + "A" + b +"B\n"NOR +
                 HIG"�㻹��"NOR HIY + (8 - me->query("hulu/guess/time")) +
                 NOR HIG"�λ�����Բ¡�\n"NOR);    */

            msg = HIC"������Ĵ����У�\n"NOR;
            msg += call_other(TEXT2PIC_D,"Display",a + "A" + b +"B");
            msg += HIG"\n�㻹��"NOR HIY + (8 - me->query("hulu/guess/time")) +
                   NOR HIG"�λ�����Բ¡�\n"NOR;
            write(msg);
      }
      else
      {
           for (i=0;i<4;i++)
           {
               number += me->query("hulu/number/"+i);

           }

           me->delete("hulu/guess");
           write(HIR"���ϧ���˴����㻹��û���У�����:"NOR
                     HIG + number + NOR HIR
                     "\n���ڸ��㻻���������¿�ʼ�¡�\n"NOR);
           call_other(HULU_INSIDE, "set_number",me);
      }

   }

   return 1;

}

int do_giveup()
{
    object me;
    me = this_player();
write("��������������,�������ȥ��!\n");
return 1;

    tell_object( me, HIR"��ô�ͷ����ˣ���û��Ϣ��������\n");
    message_vision(HIC"$N����ɥ����ͷɥ����˵�����������������ˣ����ҳ�ȥ"
                   "�ɣ���\nֻ����«��ͻȻ���˿�����$Nವ�һ�����˳�ȥ��\n"NOR,
                   me);

    me->delete("hulu");
    me->set("startroom", "/d/city/kedian/");
    me->move("/d/city/kedian");

    tell_object(me, HIG"�����ܵ���Ǵ����ĸ��ţ����Ȥζ������ȡ���ˡ�"
                "���������ɣ�\n"NOR);
        if ( me->query("weiwang") > 10000 && me->query("score") > 10000 )
        {
           me->add("weiwang", -100);
           me->add("score", -100);

           tell_object(me, HIR"��������ͽ��������յ���һ����ʧ��\n"NOR);
        }
    me->delete("xquest");
    me->set("xquest_count",0);
    me->set("xquest_last_cancel", time());
    me->add("xquest_total_cancel/total", 1);

    return 1;
}
