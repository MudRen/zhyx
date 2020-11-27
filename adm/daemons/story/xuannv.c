// story:xuannv ��Ů

#include <ansi.h>

inherit F_CLEAN_UP;

mixed random_gift();

static mixed *story = ({
        "��磬Ů洹�......",
        "Ů�:��,�����������ơ�",
        "��Ů:��֪����Ϊ���·��գ�",
        "Ů�:����½�����Ů��֮����ʢ�����������ұ�Ů����������֮�ء�",
        "��Ů:��ѽ����������Ů����������֮����������תѽ��",
        "Ů�:������ˣ����������Ů������޹�ѽ��",
        "��Ů:��������Ů�������½�����Ϊ�ۣ�����Ů�٣�",
        "Ů�:Ҫ�����½�Ϊ��̫���鷳����Ҫ�����׼��",
        "��Ů:�ǿ�����Ǻ��أ�",
        "Ů�:�ҿ��������½���ѡ����Ů��,���������Ů֮��,����߳�����,����ü��Ŀ�࿴��",
        "��Ů:�˷����ã������ȥ����Ѱ�ҡ�",        
        (: random_gift :),
});

void create()
{
        seteuid(getuid());
}

string prompt() { return HIM "��������Ů��" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

mixed random_gift()
{
        object *obs;
        object ob;
        string msg;
        mapping my;
        int select;

        select = 0;
        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 environment($1) &&
                                           //      environment($1)->query("outdoors") &&
                                                 $1->query("gender") == "Ů��" &&    
                                                 ! $1->query("special_skill/emperor") &&  
                                                 ! $1->query("special_skill/lonely") &&  
                                                 ! $1->query("special_skill/queen") &&                                                                       
                                                 ! $1->query("doing") :));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        
        if (random( 5200 -  ob->query("kar") * 100 ) > 0 )       
        {
                msg = HIC "��Ů��" + ob->name(1) +
                      HIC "���Ǹ�Ե���㣬��������޺�����ѡ�������˴�Ҫ�޹������ˡ�" NOR;
                ob->add("kar", 1+random(2));
                if ( ob->query("kar") >= 50 ) ob->set("kar",50);

        } else
        {
                msg = HIY "��Ů������" + ob->name(1) +
                      HIY "��Ů��ϡ�е�������֮������������ʤ����Ůһְ��" NOR;
                ob->set("special_skill/queen", 1);
                ob->set("special_skill/youth", 1);
                ob->set("per", 40);
                log_file("static/tianzi", sprintf("%s(%s) �����Ů���� at %s.\n",
                         ob->name(1), ob->query("id"), ctime(time())));
                select = 1;

        }
        remove_call_out("announce");
        call_out("announce",1,select,ob);
        return msg;
}

void announce(int select, object ob)
{
      if (select == 0 )
      CHANNEL_D->do_channel(this_object(), "rumor",
         "��˵Ŀǰ��������������Ů֮������ѡ,��Ů洸�" + ob->name() +"���˸�Ե�Թۺ�Ч��\n");
      else
      CHANNEL_D->do_channel(this_object(), "rumor",
           "��˵" + ob->name() + "��Ů�ѡ�г�Ϊ������Ů��\n");
}
