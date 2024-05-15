#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>
#include "../ap_12.12/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework; 

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            Node* root = nullptr;
            insert(root, new Student("Biba", 85, 90, 92));
            insert(root, new Student("Boba", 78, 82, 80));
            insert(root, new Student("Ailliams", 90, 95, 88));

            string result;
            auto inorderTest = [&](Node* node) {
                if (node != nullptr) {
                    inorder(node->left);
                    result += node->data->surname + " ";
                    inorder(node->right);
                }
                };
            inorderTest(root);
            Assert::AreEqual(string("Biba "), result);
		}
	};
}
