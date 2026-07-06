/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Keywords used in the OpenDraft language.
 */
public enum Keyword {
    UNDEFINED,
    FALSE,
    TRUE;

    static Keyword fromString(String str) {
        if (str == null) {
            return UNDEFINED;
        }

        switch (str) {
            case "false":
                return FALSE;
            case "true":
                return TRUE;
            default:
                return UNDEFINED;
        }
    }
}
