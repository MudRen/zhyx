//by xiner 2009-07-05����special��ѯ
#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object* users;
        int count, i, j;
        
        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

//        users = all_interactive();
	users = users();

        if (wiz_level(me) < 4)
                return 0;
  
        if (! str)
                return notify_fail("��Ҫͳ��ʲô�ؼ���\n");

        if (file_size("/kungfu/special/" + str + ".c") == -1)
                return notify_fail("û������ؼ����ڣ�\n");

        count = sizeof(users);

        j = 0;
        write(HIW "\n����Ϊ��MUD������ " + HIM + CHINESE_D->chinese(str) + HIW + " ����ҡ�\n" NOR);
        write(HIY "-------------------------------------------------------------------------\n" NOR);
        for (i = 0; i < count; i ++)
        {
             if (users[i]->query("special_skill/" + str))
             {
                  write(HIC + users[i]->name() + "(" + users[i]->query("id") + ") \t\t" NOR);
                  write(HIC "���䣺" + users[i]->query("age") + "\t" NOR);
                  write(HIC "�������ɣ�" + users[i]->query("family/family_name") + "\t" NOR);
                  write(HIC "�ȼ���" + users[i]->query(str) + "\n" NOR);
                  j ++;
             }
         
        }
        write(HIW "\n�ܹ� " HIR + j + HIW " λ��Ҿ���" + HIM + CHINESE_D->chinese(str) + HIW +" �����⼼�ܡ�\n" NOR);
        write(HIY "-------------------------------------------------------------------------\n" NOR);

        return 1;
}

