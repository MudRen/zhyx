#include <ansi.h>

#define BOOK_DIR "/clone/lonely/book/"
int get_book();

static mixed *story = ({
        "����Ӣ�۴��󣬹���������",
        "Ľ�ݸ���������С��̫�ɺ��ˣ���Ȼ���������ң�",
        "�˰ٴ�����������������ʵ������ѽ��",
        "����ͬ����Ҳ��Ҳ����Ľ�ݼҵĲκ�ָ�������������񽣡�",
        "Ľ�ݸ����µ����ֻ��ǿ�������κ�ָ�ˣ�",
        "��ұǬ�����ǹ��ӣ���˵�����κ�ָ����İ���ָ���ؼ������佭������֪�ں���֮�֡�",
        "�粨���޷������������˾ͳ�ׯѰ�ң���Ϊ����ȡ���ؼ���",
        (: get_book :),
        "���պ�",
});

string *books = ({
        "lianhuazhi",
        "qixingzhi",
        "tianlongzhi",
        "qilian",
        "youmingzhi",
        "tianzhuzhi",
        "duoluoyezhi",
        "xiuluozhi",
        });

string *finder = ({"�˰ٴ�", "����ͬ", "��ұǬ", "�粨��"});

string prompt() { return HIW "���������¡�" NOR; }

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
        object ob, book, owner;
        int i = sizeof(books);
        string temp, *find_book = ({});

        while(i--) {
                ob = find_object(BOOK_DIR + books[i]);
                if(objectp(ob)) {
                        find_book += ({ob->name()});
                        if(objectp(environment(ob)) && userp(environment(ob))) {
                                owner = environment(ob);
                                tell_object(owner, "��ͻȻ���е�����һʹ������Ӳ�����һ�¡�\n");
                                owner->unconcious();
                        }
                        destruct(ob);
                                }
        }
        if (! i = sizeof(find_book)) {
                story += ({finder[random(sizeof(finder))] + "�����ӣ��������ܣ��ڽ������˵���ô��Ҳû��Ϊ���ҵ�һ�����š�"});
                story += ({"Ľ�ݸ����ⲻ���㣬��Ϊ���Ѿ��ռ����������������ˡ�"});
        } else {
                temp = find_book[--i];
                if(i) {
                        while(--i) temp += "��" + find_book[i];
                        temp += "��" + find_book[0];
                }
                story += ({finder[random(4)] + "�����ӣ����ҵ���" + temp + "���㿴��"});
                story += ({"Ľ�ݸ���̫���ˣ����������ɲκ�ָ�����ˡ�"});
        }
        return 1;
}
