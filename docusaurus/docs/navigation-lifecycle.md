---
id: navigation-lifecycle
title: Navigation Lifecycle
sidebar_label: Navigation Lifecycle
---

convert to reasonml from <https://reactnavigation.org/docs/en/navigation-lifecycle.html#example-scenario>

This gif demonstrates how all screens remain mounted even when you navigate away. Notice that on the `HomeStack` we navigate to `Details` then we navigate to the `Settings` stack via the tabs at the bottom. When we navigate back to the `HomeStack` we are still on the `Details` screen in that stack since that is the screen we were on when we left it.

![navigation-lifecycle](../images/lifeCycleDemo.gif)
