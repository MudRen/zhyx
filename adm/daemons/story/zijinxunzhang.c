// story:zijinxunzhang �Ͻ�ѫ��

#include <ansi.h>

inherit F_CLEAN_UP;

mixed random_gift();

nosave mixed *story = ({
        "�Ϲţ����",
        "�̹�:��Ů洣��ܾò�������Ȼ��ôƯ������",
        "Ů�:��Ӵ��������˽�������ô��ô�𣿡�",
        "�̹�:���������ҾͿ��İ���������Ҫ����һ����������˵�գ��̹��ó�һ���������Ķ����ݸ�Ů洡�",
        "Ů洽ӹ���һ�����ʵ�:������ʲô��������",
        "�̹�:�������Ͻ�ѫ�£��������У��ҽ���ò����ײ�����·�ϼ�һ�顣��",
        "Ů�:��ƽ���޹����˶����������������Ұɣ���",
        "�̹������룬��:���㿴������ʶҲ��ô���ˣ�Ҫ������������һ����ɡ���",
        "Ů���ɫ��ৡ���һ�¾ͺ��ˣ��������",
        "�̹�:�������л��ǲ��У���˵�仰ѽ����",
        "Ů�:�������Ѿ����������ˣ��㻹�ǻ����˰ɡ���",
        "�̹������쳣��һ������ѫ�£�Ťͷ���ˣ�����Ů�������վ�š�",
        "�̹�����:�����̵ģ��㿴�����ң����Ӵ�Խ������������ȥ��",
        "�̹�:����ѽ�����ˣ��ҵ�ѫ����ȥ�ˣ���",
        (: random_gift :),
});

void create()
{
        seteuid(getuid());
}

string prompt() { return HIM "���Ͻ�ѫ�¡�" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

mixed random_gift()
{
        object *obs;
        object ob;
        object *gobs;
        object gob;
        string msg;
        mapping my;
        int select;

        select = 0;

        gobs = ({
                "/clone/fam/max/learn-emblem.c",
                "/clone/fam/max/practice-emblem.c",
                "/clone/fam/max/research-emblem.c",
                "/clone/fam/max/research-emblem2.c",
        });
        gob = gobs[random(sizeof(gobs))];
        obs = filter_array(all_interactive(), (:  ! wizardp($1) &&
                                                 living($1) &&
                                                 $1->query("kar") > 40 &&
                                                 $1->query("per") < 20 &&
                                                 environment($1)->query("outdoors") &&
                                                 ! $1->query("story/zijinxunzhang") &&
                                                 ! $1->query("doing") :));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];

        if (random( 5200 -  ob->query("kar") * 100 ) > 0 )
        {
                msg = HIC "�̹ţ�" + ob->name(1) +
                      HIC "��ѫ�»��ң������̵ģ���Ҳ�����ⶫ����˵��һ������ѫ�¡�" NOR;

        } else
        {
                msg = HIY "�̹ţ�����" + ob->name(1) +
                      HIY "��Ȼ�Ҽ����ӵĶ������´α������������Ĳ�������" NOR;
                gob->move(ob, 1);
                ob->set("story/zijinxunzhang", 1);
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
         "��˵" + ob->name() +"��͵�̹ŵ��Ͻ�ѫ�£�������˷��ֱ�ʹ����һ�١�\n");
      else
      CHANNEL_D->do_channel(this_object(), "rumor",
           "��˵" + ob->name() + "����������Ͻ�ѫ�¡�\n");
}
