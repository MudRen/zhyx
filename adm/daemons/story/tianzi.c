// story:tianzi ����

#include <ansi.h>

inherit F_CLEAN_UP;

mixed random_gift();

static mixed *story = ({
        "ĳ��ĳ�µ�ĳһ��...",
        "�Ƶۺ��׵�����...",
        "�Ƶۣ��ֵܣ����Ƕ����ˣ������ɽ��ˡ�",
        "�׵ۣ�Ŷ����������Ҫ��һ�ߣ���˭����������֮λ����",
        "�Ƶۣ��������Σ�",
        "�׵ۣ��Ҷ��ӣ�����ɵ�ˣ��Ҷ��������ˣ��������������",
        "�Ƶۣ�������С�ӱ����û��Ϣ�ˣ������Ű�֥����ɽ��ȥ�ˣ�˵�ǲ�����ɽ�����ˣ�",
        "�׵ۣ�������ô�������������丸�������ӣ�",
        "�Ƶۣ��������˵�˵��������ǰ칫ʱ�䣬Ҫ̸�����£�",
        "�׵ۣ�9494���������ƣ�û�нӰ��������ϲ����ɽ�ѽ��",
        "�Ƶۣ����ˣ��ҿ����������һ�������ɡ�",
        "�׵ۣ��ţ�ֻ����ô���ˡ��������ȥ������û�к��ʵ����Ҹ����̳�������֮λ�ɣ�",
        (: random_gift :),
});

void create()
{
        seteuid(getuid());
}

string prompt() { return HIY "���������ӡ�" NOR; }

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
                                              //   environment($1)->query("outdoors") &&
                                                 $1->query("gender") == "����" && 
                                                 ! $1->query("special_skill/emperor") &&  
                                                 ! $1->query("special_skill/lonely") &&  
                                                 ! $1->query("special_skill/queen") &&                                             
                                                 ! $1->query("doing") :));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        
        if (random( 5200 -  ob->query("kar") * 100 ) > 0 )       
        {
                msg = HIC "����װ����������˳�" + ob->name(1) +
                      HIC "����ϸϸ�����˰��죬�����ҡҡͷ���ˡ�" NOR;
                ob->add("kar", 1+random(2));
                if ( ob->query("kar") >= 50 ) ob->set("kar",50);

        } else
        {
                msg = HIY "�Ƶۣ������ֿ���" + ob->name(1) +
                      HIY "������ò�������Ǹ����棬ȷʵ�Ǽ̳е�λ�Ĳ�����ѡ��" NOR;
                ob->set("special_skill/emperor", 1);
                ob->set("special_skill/youth", 1);
                ob->set("per",40);
                log_file("static/tianzi", sprintf("%s(%s) ����������� at %s.\n",
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
         "��˵�ס��ƶ���Ѱ�����������޹�����,����" + ob->name() + "���˸�Ե��\n");
      else
      CHANNEL_D->do_channel(this_object(), "rumor",
           "��˵" + ob->name() + "���ס��ƶ���ѡ�У��ٵ���������֮λ��\n");
}
