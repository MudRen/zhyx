#include <ansi.h>

#define BOOK_DIR "/clone/lonely/book/"
int get_book();
int get_book2();

static mixed *story = ({
        "�����ɣ����ӣ���˵������������κ�ָ�������㱨�����������Ҳ����һ�°ɣ�",
        "���������.........",
        "������ԩ���˽ⲻ�˽ᣬ�ο���Ź��ɱ����Υ���������̹ٸ�֪�������Ĳ��㡣",
        "ľ���壺.............����һ����ľͷ��",
        "���飺�ѵ�Ľ�ݹ���Ҫ�����������Ҳ����ô������",
        "���������...���...",
        "�����ɣ�����Ĳ��ܣ�����",
        "���������ǲ��ǣ�ֻ���ҼҾ���ѧ���佭����ȱ�������޷���������",
        "ľ���壺�⵹���޷����������Ǿ��س�������Ѱ�Ҿ���ѧ����",
        "���飺�ð��ð������ó�ȥ���棡",
        "�������������Ƕ�ȥ������",
        "ľ���壺��Ȼ����Ȼ����һ���˳�ȥ����֪���Ҽ�����������",
        "������................",
        "���պ�",
        (: get_book :),
        "��������λ��̨��С���������ҼҾ���ѧ��Ҳ������ã���֪�ɷ��ͻ����ң�",
        "ĳ�ˣ�..........",
        "ľ���壺�����ϻ���ô�࣡�����ҵ��������",
                (: get_book2 :),
        "ĳ�˲ҽ�һ��������",
        "��˵ĳ�˲��ⶾ�֣�����ѧ���ᣡ",
});

string *books = ({
        "jingluoxue1",
        "jingluoxue2",
        });

string prompt() { return HIW "���������¡�" NOR; }

object ob;

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int get_book()
{
        int i = random(2);

        ob = find_object(BOOK_DIR + books[i]);
                if(!objectp(ob)) ob = find_object(BOOK_DIR + books[!i]);
                if(!objectp(ob)) {
                        story = allocate(20);
                        story[15] = "�������⼸�������˴�ú�ɽ��ʵ�˿��գ�";
                        story[16] = "ľ���壺�鶼û���ҵ�����֪���棬û��Ϣ��";
                        story[17] = "���飺����������ѽ���Ҿ�����Щ����������ĵġ�";
                        story[18] = "���������������֪�����⡣";
                        story[19] = "����һ��������޹�������";
                }
                return 1;
}

int get_book2()
{
        object owner;
        if(objectp(environment(ob)) && userp(environment(ob))) {
                owner = environment(ob);
                tell_object(owner, "ֻ��һ�����⣬һ������������ؿڡ�\n");
                owner->unconcious();
        }
        destruct(ob);
                return 1;
}
