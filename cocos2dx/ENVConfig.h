#ifndef __ENVCONFIG_H__
#define __ENVCONFIG_H__

/**
 * We can config some features, such as handset/language/airline and so on.
 * If any have more features, we can add enum right here,
 * it will be used by jenkins through parameter.
 */
#define env_hainan_default      0
#define env_airchina            1
#define env_tibet               2
#define env_xiamen              3
#define env_envee               4
#define env_envee_nohandset     5


#define ENVEE_FEATURES  env_hainan_default
//#define ENVEE_FEATURES  env_envee_nohandset


#endif // __ENVCONFIG_H__

