#ifndef __ENVCONFIG_H__
#define __ENVCONFIG_H__

/**
 * We can config some features, such as handset/language/airline and so on.
 * If any have more features, we can add enum right here,
 * it will be used by jenkins through parameter.
 */
enum {
    env_hainan_default = 0,
    env_airchina,
    env_tibet,
    env_xiamen,
    env_envee,
    env_envee_nohandset,
};

#define ENVEE_FEATURES  env_hainan_default
//#define ENVEE_FEATURES  env_envee_nohandset


#endif // __ENVCONFIG_H__

