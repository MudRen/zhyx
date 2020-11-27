// versiond.c

#include <ansi.h>
#include <runtime_config.h>
#include <getconfig.h>
#include <net/socket.h>

// #pragma optimize
// #pragma save_binary

inherit F_DBASE;
inherit F_SAVE;


// 为一个文件增加保证完整的鉴别ID
int append_sn(string file)
{
        string ckey;
        string text;
        int len;

        switch (file_valid(file))
        {
        case 0:
                // 目前的鉴别 ID 是错误的
                text = read_file(file);
                len = strsrch(text, "\n");
                text = text[len + 1..<1];
                write_file(file, text, 1);

                // 删除鉴别ID以后继续向下执行

        case -2:
                // 目前没有鉴别ID
                ckey = file_crypt(file);
                text = read_file(file);
                text = sprintf("// SN:%s\n%s", ckey, text);
                write_file(file, text, 1);
                return 1;

        case -1:
                // 没有这个文件
                return -1;

        default:
                // 已经有了正确的鉴别ID
                return 1;
        }
}
