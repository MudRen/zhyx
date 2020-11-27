// whisper.c

#include <ansi.h>

inherit F_CLEAN_UP;

int reply_whisper(object me, object who, string msg);

int main(object me, string arg)
{
	string dest, msg;
       int r;
	object ob;
        object env;
        mixed info;

	if (! arg )
       return notify_fail("��Ҫ��˭����Щʲô��\n");
       if ( sscanf(arg, "%s to %s", msg, dest) != 2 
            && sscanf(arg, "%s %s", dest, msg) != 2 )
	return notify_fail("ָ���ʽ��whisper <ѶϢ> to <ĳ��>\n");

        env = environment(me);
	ob = present(dest, env);

	if (! ob || ! ob->is_character())
		return notify_fail("��Ҫ��˭���\n");

        if (ob == me)
		return notify_fail("���޷�����յ��Լ��Ķ�����˵����\n");

        if (me->ban_say(1))
                return 0;

        if (info = env->query("no_say"))
        {
                if (stringp(info))
                {
                        write(info);
                        return 1;
                }

                write("����ط����ܽ�����\n");
                return 1;
        }

        if (me->query("doing") == "scheme")
        {
                if (me->query("jing") < 100)
                        return notify_fail("�����ڵľ��񲻼ã���һ����ɡ�\n");
                me->add("jing", -50);
        }

	write(WHT "����" + ob->name() + WHT "�Ķ�������˵����" +
	      msg + "\n" NOR);
	tell_room(environment(me), me->name() + "��" + ob->name()
		+ "����С����˵��Щ����\n", ({ me, ob }));

	if (! userp(ob)) ob->relay_whisper(me, msg);
	else
		tell_object(ob, WHT + me->name() +
				WHT "����Ķ�������˵����" + msg + "\n" NOR);
      //��ϳ�����������������������
       if ( ! userp(ob) )
       {
          if ( me->query("changanjob/kind") != "whisper" ||
               me->query("changanjob/target") != ob->name() )  
              tell_room(environment(me), CYN + ob->name() + "˵����"NOR + HIG
              "�����Ҷ��߼�������˵ʲô?����ţͷ�������졣\n"NOR);
          else
              {
                 if ( me->query("changanjob/whisper") )
                 {
                      tell_room(environment(me), CYN + ob->name() + "˵����"NOR 
                                 + HIG "��,��л�Ѱ��Ŵ�����\n"NOR);           
                      if ( me->query("changanjob/whisper") == msg )
                           me->set("changanjob/ok",1);                     
                      me->delete("changanjob/whisper");  
                 } else
                 {
                      tell_room(environment(me), CYN + ob->name() + "˵����"NOR 
                                  + HIG"���Ѿ������Ұ�����ѽ!\n"NOR);   
                 }            
                 
	if (! userp(ob)) 
       {
              r = 0;
              if (me->query("bang_quest") && me->query("bang_quest/type") == "������")
                      r = reply_whisper(me,ob,msg);
              if (!r)
                      ob->relay_whisper(me, msg);
       }
	else
		tell_object(ob, WHT + me->name() +
				WHT "����Ķ�������˵����" + msg + "\n" NOR);
               }
       }
	return 1;
}

int reply_whisper(object me, object who, string msg)
{
        mapping bang_quest,b;

        int exp;
        int pot;
        int score;
        int weiwang;

        bang_quest = me->query("bang_quest");

        //��������
        if (bang_quest["target"] != base_name(who))
                return 0;

        //������
        if (msg != bang_quest["send_msg"])
                return 0;

        message_sort("$N��ɫ���أ�һ������һ�߶�$nʹ���ĵ�ͷ������λ" +
                     RANK_D->query_respect(who) +
                     "����л��ѻ���������\n", who, me);

        // ����
        me->add("pk_score",-2);
        if (me->query("pk_score") < 0) me->set("pk_score",0);

        exp = bang_quest["bonus"];
        exp += random(exp/2);
        exp += me->query("combat_exp")/5000;
        pot = exp/(2 + random(2));
        score = 5 + random(10);
        weiwang = 5 + random(10);

        b = ([ "exp" : exp,
               "pot" : pot,
               "score" : score,
               "weiwang" : weiwang,
               "prompt": "�ڰѿ��Ŵ���" + who->name() +
                         HIG "�Ĺ����У���������" ]);

        QUEST_D->delay_bonus(me, b);

        me->delete("bang_quest");
        me->add_temp("finish_bang_times",1);

        return 1;
}
int help(object me)
{
	write( @TEXT
ָ���ʽ��whisper <ѶϢ> to <ĳ��> 

���ָ�����������ͬһ�����е��˶������ NPC ���ڡ�
TEXT );
	return 1;
}
